/*
 * @Project      :
 * @FilePath     : \Code\network\dataLinkLayer.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:58:59
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-27 01:45:19
 */
#include "dataLinkLayer.hpp"
#include "physicalLayer.hpp"
#include "networkLayer.hpp"

DataLinkLayer::DataLinkLayer(Config::ConfigBean cfg, NetworkLayer* nlPtr) {
    physicalLayer = new PhysicalLayer(cfg);
    eventQueue = new GBNEventQueue();
    networkLayerPtr = nlPtr;

    DATA_SIZE = cfg.dataSize;
    SW_SIZE = cfg.swSize;
    TIMEOUT = cfg.timeout;
    INIT_SEQ_NO = cfg.initSeqNo;
}

void DataLinkLayer::init() {
    ack_expected = 0;       /* next ack_expected inbound */
    next_frame_to_send = 0; /* next frame going out */
    frame_expected = 0;     /* number of frame_expected inbound */
    nbuffered = 0;          /* initially no packets are buffered */

    init_timer(); /* initialize the timer */

    isRunning = true;
    eventHandler = std::thread([this]() {
        while (isRunning) {
            this->handleEvents();

            // debug
            // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    physicalLayer->init();
    physicalLayer->startRecvTask(this);
    // physicalLayer->startRecvTask();
    enable_network_layer(); /* allow network layer ready events */
}
DataLinkLayer::~DataLinkLayer() {
    isRunning = false;
    eventHandler.join();
    delete physicalLayer;
    delete eventQueue;
}

inline bool DataLinkLayer::between(uint8_t a, uint8_t b, uint8_t c) {
    /* Return true if a < b <= c circularly; false otherwise. */
    if (((a < b) && (b <= c)) || ((c <= a) && (a < b)) || ((b <= c) && (c < a)))
        return (true);
    else
        return (false);
}

inline int DataLinkLayer::inc(uint8_t& num) {
    if (num < MAX_SEQ)
        num++;
    else
        num = 0;
    return num;
}

int DataLinkLayer::sendData(PhyAddrPort ap, std::string packet) {
    /* Construct and send a data frame. */
    Frame s(
        FRAME_TYPE::DATA,   /* type == data */
        next_frame_to_send, /* insert sequence number into frame */
        frame_expected,     /* piggyback ack */
        packet              /* insert packet into frame */
    );
    physicalLayer->sendData(s.to_buff_all(), ap); /* transmit the frame */
    isACKsent = true;
    start_timer(next_frame_to_send); /* start the timer running */
    return 0;
}

int DataLinkLayer::sendACK(PhyAddrPort ap) {
    // return 2;
    if (!isACKsent)
        return 1;
    isACKsent = false;
    ackTime = new Timer([ap, this]() {
        if (this->isACKsent) {
            std::cout << "[DataLinkLayer][INFO] ACK already sent, abort" << endl;
            return;
        }
        Frame s(FRAME_TYPE::ACK, 0, this->frame_expected, "");
        physicalLayer->sendData(s.to_buff_all(), ap);
        isACKsent = true;
    },
                        TIMEOUT / 5);
    ackTime->start();
    return 0;
}
int DataLinkLayer::sendNAK(PhyAddrPort ap, uint8_t seq) {
    Frame s(FRAME_TYPE::NAK, 0, seq, "");
    physicalLayer->sendData(s.to_buff_all(), ap);
    return 0;
}

int DataLinkLayer::reSendAllData() {
    for (int i = 0; i < nbuffered; i++) {
        GBN_EVENT event = buffer[next_frame_to_send];
        PhyAddrPort ap = event.ap;
        std::string packet = event.packet;
        sendData(ap, packet);    /* resend frame */
        inc(next_frame_to_send); /* prepare to send the next one */
    }
    return 0;
}
void DataLinkLayer::handleEvents() {
    GBN_EVENT event = eventQueue->get(); /* four possibilities: see event type above */
    Frame::Header header = event.header; /* get incoming frame from physical layer */
    std::string packet = event.packet;   /* fetch new packet */
    PhyAddrPort ap = event.ap;
    switch (event.type) {
        case GBN_EVENT_TYPE::NETWORK_LAYER_READY: /* the network layer has a packet to send */
            std::cout << "[DataLinkLayer][INFO] NETWORK_LAYER_READY sending " << int(next_frame_to_send) << std::endl;
            Debug::logAT(this, next_frame_to_send, event.type);
            /* Accept, save, and transmit a new frame. */
            buffer[next_frame_to_send] = event; /* insert event into buffer */
            nbuffered++;                        /* expand the sender’s window */
            sendData(ap, packet);               /* transmit the frame */
            inc(next_frame_to_send);            /* advance sender’s upper window edge */
            break;
        case GBN_EVENT_TYPE::FRAME_ARRIVAL: /* a data or control frame has arrived */
            std::cout << "[DataLinkLayer][INFO] FRAME_ARRIVAL" << std::endl;
            switch (header.type) {
                case FRAME_TYPE::DATA:
                    // std::cout << "[DataLinkLayer][INFO] header.type DATA" << std::endl;
                    /* Frames are accepted only in order. */
                    if (header.seq == frame_expected) {
                        std::cout << "[DataLinkLayer][INFO] header.type DATA accepted" << int(frame_expected) << std::endl;
                        Debug::logAR(this, header.seq, "OK");

                        to_network_layer(ap, packet); /* pass packet to network layer */
                        inc(frame_expected);          /* advance lower edge of receiver’s window */
                        sendACK(ap);                  /* acknowledge the frame */
                    } else {
                        Debug::logAR(this, header.seq, "NoErr");
                    }
                    // break; //support data with ack piggyback
                case FRAME_TYPE::ACK:
                    // std::cout << "[DataLinkLayer][INFO] header.type ACK" << std::endl;
                    /* Ack n implies n − 1, n − 2, etc. Check for this. */

                    while (between(ack_expected, header.ack, next_frame_to_send)) {
                        std::cout << "[DataLinkLayer][INFO] header.type ACK accept " << int(ack_expected) << std::endl;
                        // Debug::logAR(this, header.seq, "ACK");

                        /* Handle piggybacked ack. */
                        nbuffered--;              /* one frame fewer buffered */
                        stop_timer(ack_expected); /* frame arrived intact; stop timer */
                        inc(ack_expected);        /* contract sender’s window */
                    }
                    break;
                case FRAME_TYPE::NAK:
                    std::cout << "[DataLinkLayer][INFO] header.type NAK go back to " << int(header.ack) << std::endl;
                    /* Sender will receive frame_expected − 1 next time. */
                    next_frame_to_send = header.ack; /* start retransmitting here */
                    reSendAllData();                 /* resend buffered frames */
                    break;
                default:
                    std::cout << "[DataLinkLayer][ERROR] Unexpected frame type" << std::endl;
                    break;
            }
            recvCount++;

            break;
        case GBN_EVENT_TYPE::CKSUM_ERR:
            std::cout << "[DataLinkLayer][ERROR] Checksum error for " << int(header.seq) << std::endl;
            Debug::logAR(this, header.seq, "DataErr");
            sendNAK(ap, header.seq);
            break;
        case GBN_EVENT_TYPE::TIMEOUT: /* trouble; retransmit all outstanding frames */
            std::cout << "[DataLinkLayer][TIMEOUT] go back to " << int(ack_expected) << std::endl;
            next_frame_to_send = ack_expected; /* start retransmitting here */
            reSendAllData();                   /* resend buffered frames */
    }
    if (nbuffered < MAX_SEQ)
        enable_network_layer();
    else
        disable_network_layer();
}

void DataLinkLayer::init_timer() {
    timerList.clear();
    // timerList.resize(SW_SIZE);
    for (size_t i = 0; i < MAX_SEQ + 1; i++) {
        Timer* t = new Timer([this, i] {
            unique_lock<mutex> lock(mtx_timer);
            std::cout << "[DataLinkLayer] time out for seq_id " << i << endl;
            // stop all other timers
            for (size_t j = 0; j < MAX_SEQ; j++) {
                this->stop_timer(j);
            }
            this->eventQueue->put({
                GBN_EVENT_TYPE::TIMEOUT,
                Frame::Header(),
                "",
                PhyAddrPort(),
            });
        },
                             TIMEOUT);
        timerList.push_back(t);
    }
}

void DataLinkLayer::stop_timer(uint8_t frame_num) {
    timerList[frame_num]->stop();
}

void DataLinkLayer::start_timer(uint8_t frame_num) {
    stop_timer(frame_num);
    timerList[frame_num]->start();
}

void DataLinkLayer::enable_network_layer() {
    // std::cout << "[DataLinkLayer] enable network layer" << std::endl;
    isNetworkLayerEnabled = true;
}

void DataLinkLayer::disable_network_layer() {
    // std::cout << "[DataLinkLayer] disable network layer" << std::endl;
    isNetworkLayerEnabled = false;
}

void DataLinkLayer::to_network_layer(PhyAddrPort ap, std::string packet) {
    // std::cout << "[DataLinkLayer] to network layer" << std::endl;
    if (networkLayerPtr != nullptr) {
        networkLayerPtr->onDataLinkLayerRx(RecvData(ap, packet));
    }
}

void DataLinkLayer::onPhysicalLayerRx(RecvData data) {
    Frame frame(data.buff);
    if (frame.verify()) {
        eventQueue->put({
            GBN_EVENT_TYPE::FRAME_ARRIVAL,
            frame.header,
            frame.info,
            data.ap,
        });
    } else {
        // @Todo:如果ack有问题咋办
        eventQueue->put({
            GBN_EVENT_TYPE::CKSUM_ERR,
            frame.header,
            frame.info,
            data.ap,
        });
    }
}

void DataLinkLayer::onNetworkLayerTx(PhyAddrPort ap, std::string packet) {
    // wait for isNetworkLayerEnabled to be true
    while (!isNetworkLayerEnabled) {
        // this thread sleep for 10ms
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    eventQueue->put({GBN_EVENT_TYPE::NETWORK_LAYER_READY,
                     Frame::Header(),
                     packet,
                     ap});
}

void DataLinkLayer::testDLL(PhyAddrPort ap) {
    sendACK(ap);
}

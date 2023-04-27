/*
 * @Project      :
 * @FilePath     : \Code\network\networkLayer.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:59:13
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-28 00:23:42
 */

#include "networkLayer.hpp"
#include "dataLinkLayer.hpp"

NetworkLayer::NetworkLayer(Config::ConfigBean cfg) {
    this->cfg = cfg;
    dataLinkLayer = new DataLinkLayer(cfg, this);
    packetQueue = new PacketQueue();
}

void NetworkLayer::init() {
    // if cfg.savePath not exist, create it
    if (_access(cfg.savePath.c_str(), 0) == -1) {
        std::cout << "[NetworkLayer] create savePath " << cfg.savePath << std::endl;
        _mkdir(cfg.savePath.c_str());
    }

    isRunning = true;
    packetHandler = std::thread([this]() {
        while (isRunning) {
            this->handlePackets();

            // debug
            // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    dataLinkLayer->init();
}
NetworkLayer::~NetworkLayer() {
    isRunning = false;
    packetHandler.join();
    delete dataLinkLayer;
    delete packetQueue;
}
void NetworkLayer::onDataLinkLayerRx(RecvData data) {
    std::cout << "[NetworkLayer] onDataLinkLayerRx " << std::endl;
    // Packet packet(data.buff);
    // PhyAddrPort ap = data.ap;
    // packet.print();

    packetQueue->put(data);
}

int NetworkLayer::sendHello(PhyAddrPort ap) {
    Packet helloPacket(PACKET_TYPE::HELLO, "hello!");
    dataLinkLayer->onNetworkLayerTx(ap, helloPacket.to_buff());
    return 0;
}

int NetworkLayer::sendFile(PhyAddrPort ap, std::string path) {
    // read file and deal with file not exits
    // if (!file) {
    //     std::cout << "[NetworkLayer] file not exits" << std::endl;
    //     return -1;
    // }

    std::string fileName = path.substr(path.find_last_of("\\") + 1);
    struct stat statbuf;
    stat(path.c_str(), &statbuf);
    size_t fileSize = statbuf.st_size;

    // if file not exists
    if (fileSize == 0) {
        std::cout << "[NetworkLayer] file not exits" << std::endl;
        return -1;
    }

    std::cout << "[NetworkLayer] sendFile " << fileName << " size " << fileSize << std::endl;

    // send file request
    FileRequestInfo fInfo(FileID++, fileSize, fileName);
    Packet fileRqtPacket(PACKET_TYPE::FILE_RQT, fInfo.to_buff());
    dataLinkLayer->onNetworkLayerTx(ap, fileRqtPacket.to_buff());

    // ifstream file(path, ios::binary);
    // char buff[FILE_FRAME_SIZE];
    // file.read(buff, FILE_FRAME_SIZE);
    // int size = file.gcount();
    // std::cout << buff << size << std::endl;
    // file.close();

    std::thread sendFileT([this, ap, fInfo, path]() {
        FILE* file = fopen(path.c_str(), "rb");

        unsigned packetNum = fInfo.fileSize / FILE_FRAME_SIZE + 1;

        for (int i = 0; i < packetNum; i++) {
            char buff[FILE_FRAME_SIZE];

            int size = fread(buff, 1, FILE_FRAME_SIZE, file);
            FileBuffInfo bInfo(fInfo.fileID, i * FILE_FRAME_SIZE, buff, size);
            Packet fileBuffPacket(PACKET_TYPE::FILE_BUF, bInfo.to_buff());
            dataLinkLayer->onNetworkLayerTx(ap, fileBuffPacket.to_buff());
        }

        // send File Finish
        FileFinishInfo fFinishInfo(fInfo.fileID);
        Packet fileFinishPacket(PACKET_TYPE::FILE_FIN, fFinishInfo.to_buff());
        dataLinkLayer->onNetworkLayerTx(ap, fileFinishPacket.to_buff());

        fclose(file);
    });
    sendFileT.detach();
    return 0;
}

void NetworkLayer::handlePackets() {
    // get packet from queue and swith by packet type
    RecvData data = packetQueue->get();
    Packet packet(data.buff);
    PhyAddrPort ap = data.ap;
    // packet.print();
    switch (packet.type) {
        case PACKET_TYPE::HELLO: {
            std::cout << "[NetworkLayer] recv hello from " << ap.addr << ":" << ap.port << std::endl;
            // send hello ack
            // sendHello(ap);
            break;
        }
        case PACKET_TYPE::FILE_RQT: {
            std::cout << "[NetworkLayer] recv file rqt from " << ap.addr << ":" << ap.port << std::endl;
            FileRequestInfo info(packet.info);
            Debug::logD(this, "recv file RQT from " + ap.addr + ":" + std::to_string(ap.port) + " of ["+std::to_string(info.fileID)+"]" + info.filename + "(" + std::to_string(info.fileSize) + " Bytes)");
            filesMap.insert({info.fileID,
                             FileInfo{info.fileID, info.fileSize, info.filename, ap}});
            // if file exits then delete it
            std::string path = cfg.savePath + info.filename;
            std::ofstream file(path, std::ios::binary | std::ios::trunc);
            file.close();

            break;
        }
        case PACKET_TYPE::FILE_BUF: {
            std::cout << "[NetworkLayer] recv file buf from " << ap.addr << ":" << ap.port << std::endl;
            // save file
            FileBuffInfo info(packet.info);
            FileInfo fInfo = filesMap[info.fileID];

            Debug::logD(this, "recv file BUF of " + std::to_string(info.fileID) + " +" + std::to_string(info.fileOffset));

            std::string path = cfg.savePath + fInfo.filename;
            std::ofstream file(path, std::ios::binary | std::ios::app);
            file.write(info.data.c_str(), info.data.length());
            file.close();
            break;
        }
        case PACKET_TYPE::FILE_FIN: {
            std::cout << "[NetworkLayer] recv file finish from " << ap.addr << ":" << ap.port << std::endl;

            FileFinishInfo info(packet.info);
            Debug::logD(this, "recv file ["+std::to_string(info.fileID)+"]"+filesMap[info.fileID].filename + " finished!");
            // delete filesMap[fileID] from map
            // auto index = filesMap.find(info.fileID);
            filesMap.erase(info.fileID);

            break;
        }
        default:
            std::cout << "[NetworkLayer] unknow packet type" << std::endl;
            break;
    }
}

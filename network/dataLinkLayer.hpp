/*
 * @Project      :
 * @FilePath     : \Code\network\dataLinkLayer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-23 16:06:33
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-28 00:38:12
 */
#ifndef DATALINKLAYER_HPP
#define DATALINKLAYER_HPP

#include "..\toolkit\msgQueue.hpp"
#include "..\toolkit\config.hpp"
#include "..\toolkit\Timer.hpp"
#include "Frame.hpp"
#include "DataStruct.hpp"

class PhysicalLayer;
class NetworkLayer;

// #define MAX_SEQ 7
typedef struct {
    GBN_EVENT_TYPE type;
    Frame::Header header;
    std::string packet;
    PhyAddrPort ap;
} GBN_EVENT;

typedef BlockingQueue<GBN_EVENT> GBNEventQueue;

class DataLinkLayer {
    friend class Debug;

   private:
    NetworkLayer* networkLayerPtr = nullptr;
    PhysicalLayer* physicalLayer;
    std::thread eventHandler;
    bool isRunning = false;
    GBNEventQueue* eventQueue;

    uint8_t next_frame_to_send; /* MAX_SEQ > 1; used for outbound stream */
    uint8_t ack_expected;       /* oldest frame as yet unacknowledged */
    uint8_t frame_expected;     /* next frame_expected on inbound stream */

    GBN_EVENT* buffer; /* buffers for the outbound stream */
    uint8_t nbuffered; /* number of output buffers currently in use */
    uint8_t nqueued;   /* number of network event currently in queue */
    // GBN_EVENT_TYPE event;
    mutex mtx_Nqueue;
    bool isNetworkLayerEnabled = false;
    std::condition_variable networklayer_ready;

    int DATA_SIZE;
    int SW_SIZE;
    int MAX_SEQ;
    int INIT_SEQ_NO;
    int TIMEOUT;
    bool ON_DEBUG;

    vector<Timer*> timerList;
    mutex mtx_timer;
    bool onTimeout = false;

    bool isACKsent = true;
    Timer* ackTime;
    // mutex mtx_ack;

    // Debug
    int sendCount = 1;
    int recvCount = 1;

    inline bool between(uint8_t a, uint8_t b, uint8_t c);
    inline int inc(uint8_t& num);
    void init_timer();
    void start_timer(uint8_t seq);
    void stop_timer(uint8_t seq);

    void enable_network_layer();
    void disable_network_layer();
    void update_state_network_layer();

    void to_network_layer(PhyAddrPort ap, std::string packet);

    int sendData(PhyAddrPort ap, std::string packet);
    int reSendAllData(GBN_EVENT_TYPE type);
    int sendACK(PhyAddrPort ap);
    int sendNAK(PhyAddrPort ap, uint8_t seq);
    void handleEvents();

   public:
    DataLinkLayer(Config::ConfigBean cfg, NetworkLayer* nlPtr = nullptr);
    ~DataLinkLayer();
    void init();
    void onPhysicalLayerRx(RecvData data);
    void onNetworkLayerTx(PhyAddrPort ap, std::string packet);

    void testDLL(PhyAddrPort ap);
};

#endif  // DATALINKLAYER_HPP

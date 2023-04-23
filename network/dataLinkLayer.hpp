#ifndef DATALINKLAYER_HPP
#define DATALINKLAYER_HPP

#include "Frame.hpp"
#include "physicalLayer.hpp"
#include "..\toolkit\msgQueue.hpp"
#include "..\toolkit\config.hpp"
#include "..\toolkit\Timer.hpp"

#define MAX_SEQ 7
typedef enum { FRAME_ARRIVAL,
               CKSUM_ERR,
               TIMEOUT,
               NETWORK_LAYER_READY } GBN_EVENT_TYPE;

typedef struct {
    GBN_EVENT_TYPE type;
    Frame::Header header;
    std::string packet;
    PhyAddrPort ap;
} GBN_EVENT;

typedef BlockingQueue<GBN_EVENT> GBNEventQueue;

class DataLinkLayer {
   private:
    void (*callbackFunc)(void*, RecvData)=nullptr;
    void* networkLayerPtr=nullptr;
    PhysicalLayer* physicalLayer;
    std::thread eventHandler;
    bool isRunning = false;
    GBNEventQueue* eventQueue;

    uint8_t next_frame_to_send;      /* MAX_SEQ > 1; used for outbound stream */
    uint8_t ack_expected;            /* oldest frame as yet unacknowledged */
    uint8_t frame_expected;          /* next frame_expected on inbound stream */

    GBN_EVENT buffer[MAX_SEQ + 1];  /* buffers for the outbound stream */
    uint8_t nbuffered;               /* number of output buffers currently in use */
    GBN_EVENT_TYPE event;

    bool isNetworkLayerEnabled = false;

    int DATA_SIZE;
    int ERROR_RATE;
    int LOST_RATE;
    int SW_SIZE;
    int INIT_SEQ_NO;
    int TIMEOUT;

    vector<Timer*> timerList;
    mutex mtx_timer;

    bool isACKsent = true;
    // mutex mtx_ack;

    inline bool between(uint8_t a, uint8_t b, uint8_t c);
    inline int inc(uint8_t& num);
    void init_timer();
    void start_timer(uint8_t seq);
    void stop_timer(uint8_t seq);

    void enable_network_layer();
    void disable_network_layer();
    void to_network_layer(PhyAddrPort ap, std::string packet);

    int sendData(PhyAddrPort ap ,std::string packet);
    int reSendAllData();
    int sendACK(PhyAddrPort ap);
    int sendNAK(PhyAddrPort ap, uint8_t seq);
    void handleEvents();
   public:
    DataLinkLayer(Config::ConfigBean cfg, void *nlPtr=nullptr, void (*callback)(void*, RecvData)=nullptr);
    ~DataLinkLayer();
    void init();
    static void onPhysicalLayerRx(void * queuePtr,RecvData data);
    void onNetworkLayerTx(PhyAddrPort ap, std::string packet);
};

#endif  // DATALINKLAYER_HPP

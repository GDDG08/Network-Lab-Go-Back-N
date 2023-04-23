#ifndef NETWORKLAYER_HPP
#define NETWORKLAYER_HPP


#include "dataLinkLayer.hpp"
#include "Packet.hpp"

class NetworkLayer {
    // private:
   public:
    DataLinkLayer *dataLinkLayer;
    NetworkLayer(Config::ConfigBean cfg);
    ~NetworkLayer();
    int sendFile(PhyAddrPort ap ,std::string path);
    static void onDataLinkLayerRx(void *, RecvData data);

    void init();
};

#endif // NETWORKLAYER_HPP

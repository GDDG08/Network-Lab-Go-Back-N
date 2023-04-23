#ifndef NETWORKLAYER_HPP
#define NETWORKLAYER_HPP


#include "dataLinkLayer.hpp"

class NetworkLayer {
    private:
    DataLinkLayer *dataLinkLayer;
   public:
    NetworkLayer(Config::ConfigBean cfg);
    ~NetworkLayer();
    void init();
};

#endif // NETWORKLAYER_HPP

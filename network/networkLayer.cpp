/*
 * @Project      :
 * @FilePath     : \Code\network\networkLayer.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:59:13
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 15:58:33
 */

#include "networkLayer.hpp"

NetworkLayer::NetworkLayer(Config::ConfigBean cfg) {
    dataLinkLayer = new DataLinkLayer(cfg, this, onDataLinkLayerRx);
}
NetworkLayer::~NetworkLayer() {
    delete dataLinkLayer;
}
void NetworkLayer::init() {
    dataLinkLayer->init();
}

void NetworkLayer::onDataLinkLayerRx(void* nlPtr, RecvData data) {
    std::cout<<"[NetworkLayer] onDataLinkLayerRx "<<std::endl;
    NetworkLayer* nl = (NetworkLayer*)nlPtr;
    Packet packet(data.buff);
    PhyAddrPort ap = data.ap;
    packet.print();
}

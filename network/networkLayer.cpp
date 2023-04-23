/*
 * @Project      :
 * @FilePath     : \Code\networkLayer.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:59:13
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 14:59:19
 */

#include "networkLayer.hpp"

NetworkLayer::NetworkLayer(Config::ConfigBean cfg) {
    dataLinkLayer = new DataLinkLayer(cfg);
}
NetworkLayer::~NetworkLayer() {
    delete dataLinkLayer;
}
void NetworkLayer::init() {
    dataLinkLayer->init();
}
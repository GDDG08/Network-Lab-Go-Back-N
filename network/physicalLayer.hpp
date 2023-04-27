/*
 * @Project      :
 * @FilePath     : \Code\network\physicalLayer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 15:13:27
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-27 14:07:05
 */
#ifndef PHYSICALLAYER_HPP
#define PHYSICALLAYER_HPP

// header filefor physical layer
#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>
#include <functional>
#include <random>
#include "..\toolkit\config.hpp"
#include "..\toolkit\debug.hpp"
#include "DataStruct.hpp"

// #pragma comment(lib, "ws2_32.lib")

class DataLinkLayer;

class PhysicalLayer {
    friend class Debug;

   private:
    const static int BUFF_LEN = 1024;
    int listen_port;
    int ERROR_RATE;
    int LOST_RATE;

    SOCKET sock;
    sockaddr_in recvAddr;

    bool onRecvTask = false;

   public:
    PhysicalLayer(Config::ConfigBean cfg);
    int init();
    int sendData(std::string info, PhyAddrPort ap, bool isDebug = false);
    RecvData recvData();
    int startRecvTask(DataLinkLayer* queuePtr = nullptr);
    int stopRecvTask();
    ~PhysicalLayer();
};

#endif  // PHYSICALLAYER_HPP

/*
 * @Project      :
 * @FilePath     : \Code\network\physicalLayer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 15:13:27
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 05:16:29
 */
#ifndef PHYSICALLAYER_HPP
#define PHYSICALLAYER_HPP

// header filefor physical layer
#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>
#include <functional>
#include "..\toolkit\config.hpp"

// #pragma comment(lib, "ws2_32.lib")

typedef struct {
    int port = 0;
    ULONG addr = INADDR_BROADCAST;
} PhyAddrPort;

typedef struct {
    PhyAddrPort ap;
    std::string buff;
} RecvData;
class PhysicalLayer {
   private:
    const static int BUFF_LEN = 1024;
    int listen_port;
    SOCKET sock;
    sockaddr_in recvAddr;

    bool onRecvTask = false;

   public:
    PhysicalLayer(Config::ConfigBean cfg);
    int init();
    int sendData(std::string info, PhyAddrPort ap);
    RecvData recvData();
    int startRecvTask(void* queuePtr = nullptr, void (*callback)(void*, RecvData) = nullptr);
    int stopRecvTask();
    ~PhysicalLayer();
};

#endif  // PHYSICALLAYER_HPP

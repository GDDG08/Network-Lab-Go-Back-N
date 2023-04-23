/*
 * @Project      :
 * @FilePath     : \Code\network\physicalLayer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 15:13:27
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 14:56:11
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
#include "..\toolkit\debug.hpp"

// #pragma comment(lib, "ws2_32.lib")

typedef struct {
    int port = 0;
    std::string addr = "255.255.255.255";
} PhyAddrPort;

class RecvData {
   public:
    PhyAddrPort ap;
    std::string buff;
    RecvData(PhyAddrPort ap, const char* buff_c, int size)
        : ap(ap) {
        // buff.resize(size);
        // // convert buff_c to buff for certain size of data
        // for (int i = 0; i < size; i++) {
        //     buff[i] = buff_c[i];
        // }
        buff = std::string(buff_c, size);
    }
    RecvData(PhyAddrPort ap, std::string packet)
        : ap(ap), buff(packet) {
    }
    RecvData() {}
};
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

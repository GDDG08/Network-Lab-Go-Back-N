/*
 * @Project      :
 * @FilePath     : \Code\network\physicalLayer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 15:13:27
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 20:25:59
 */
#ifndef PHYSICALLAYER_HPP
#define PHYSICALLAYER_HPP

// header filefor physical layer
#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>
// #pragma comment(lib, "ws2_32.lib")

typedef std::pair<sockaddr_in, std::string> RecvData;
class PhysicalLayer {
   private:
    const static int BUFF_LEN = 1024;
    int listen_port;
    SOCKET sock;
    sockaddr_in recvAddr;

    bool onRecvTask = false;

   public:
    PhysicalLayer(int listen_port);
    int init();
    int sendData(std::string info, int dst_port, ULONG dst_addr = INADDR_BROADCAST);
    RecvData recvData();
    int startRecvTask();
    int stopRecvTask();
    ~PhysicalLayer();
};

#endif

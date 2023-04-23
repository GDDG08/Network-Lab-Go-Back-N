/*
 * @Project      :
 * @FilePath     : \Code\network\physicalLayer.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:58:48
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 13:31:02
 */
#include "physicalLayer.hpp"

// UDP socket on windows to send and receive data

PhysicalLayer::PhysicalLayer(Config::ConfigBean cfg) {
    this->listen_port = cfg.udpPort;
}

int PhysicalLayer::init() {
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "[PhysicalLayer][Error] WSAStartup failed: " << iResult << std::endl;
        return 1;
    }
    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "[PhysicalLayer][Error] socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up the address and port to receive data from
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(listen_port);  // Port number
    recvAddr.sin_addr.s_addr = INADDR_ANY;   // Listen on all interfaces

    // Bind the socket to the receive address
    int bindResult = bind(sock, (sockaddr*)&recvAddr, sizeof(recvAddr));
    if (bindResult == SOCKET_ERROR) {
        std::cerr << "[PhysicalLayer][Error] bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    return 0;
}

int PhysicalLayer::sendData(std::string info, PhyAddrPort ap) {
    // Set up the address and port to send data to
    sockaddr_in dstAddr;
    dstAddr.sin_family = AF_INET;
    dstAddr.sin_port = htons(ap.port);                     // Port number
    dstAddr.sin_addr.s_addr = inet_addr(ap.addr.c_str());  // IP address

    // Send data
    const char* sendData = info.data();
    int sendResult = sendto(sock, sendData, info.length(), 0, (sockaddr*)&dstAddr, sizeof(dstAddr));
    if (sendResult == SOCKET_ERROR) {
        std::cerr << "[PhysicalLayer][Error] sendto failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    std::cout << "[PhysicalLayer] Sent data To "
              << inet_ntoa(dstAddr.sin_addr) << ":" << ntohs(dstAddr.sin_port) << "-->" << std::endl
              << str2hex(info) << std::endl;
    return 0;
}

RecvData PhysicalLayer::recvData() {
    // Receive data
    char buff[BUFF_LEN];
    memset(buff, 0, BUFF_LEN);
    sockaddr_in senderAddr;
    int senderAddrSize = sizeof(senderAddr);
    // use recvfrom to get sender ip port
    // int recvResult = recv(sock, buff, BUFF_LEN, 0);
    int recvResult = recvfrom(sock, buff, BUFF_LEN, 0, (sockaddr*)&senderAddr, &senderAddrSize);
    if (recvResult == SOCKET_ERROR) {
        std::cerr << "[PhysicalLayer][Error] recv failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        // exit(1);
        return RecvData();
    }
    if (recvResult == 0) {
        return RecvData();
    }

    PhyAddrPort ap = {ntohs(senderAddr.sin_port), inet_ntoa(senderAddr.sin_addr)};
    RecvData rd(ap, buff, recvResult);
    // Display the received data
    std::cout
        << "[PhysicalLayer] Received data From "
        << ap.addr << ":" << ap.port << "-->" << std::endl
        << str2hex(rd.buff) << std::endl;

    return rd;
}

int PhysicalLayer::startRecvTask(void* queuePtr, void (*callback)(void*, RecvData)) {
    std::thread recvTask([this, callback, queuePtr] {
        while (this->onRecvTask) {
            RecvData data = this->recvData();
            std::cout << "[PhysicalLayer][RecvTask] onRecv!" << std::endl;
            // msg.push_one((pi){"recv_data", tmpp});
            // if (data.buff[0] == '\0')
            //     continue;
            if (queuePtr != nullptr && callback != nullptr) {
                callback(queuePtr, data);
            }
        }
    });
    this->onRecvTask = true;
    recvTask.detach();
    return 0;
}

int PhysicalLayer::stopRecvTask() {
    this->onRecvTask = false;
    return 0;
}

PhysicalLayer::~PhysicalLayer() {
    stopRecvTask();
    closesocket(sock);
    WSACleanup();
}

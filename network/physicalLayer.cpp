/*
 * @Project      :
 * @FilePath     : \Code\physicalLayer.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:58:48
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 17:06:18
 */
#include "physicalLayer.hpp"

// UDP socket on windows to send and receive data

PhysicalLayer::PhysicalLayer(int listen_port) {
    this->listen_port = listen_port;
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

int PhysicalLayer::sendData(std::string info, int dst_port, ULONG dst_addr) {
    // Set up the address and port to send data to
    sockaddr_in sendAddr;
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(dst_port);  // Port number
    sendAddr.sin_addr.s_addr = dst_addr;  // IP address

    // Send data
    const char* sendData = info.data();
    int sendResult = sendto(sock, sendData, strlen(sendData), 0, (sockaddr*)&sendAddr, sizeof(sendAddr));
    if (sendResult == SOCKET_ERROR) {
        std::cerr << "[PhysicalLayer][Error] sendto failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
}

std::string PhysicalLayer::recvData() {
    // Receive data
    char buff[BUFF_LEN];
    int recvResult = recv(sock, buff, sizeof(buff), 0);
    if (recvResult == SOCKET_ERROR) {
        std::cerr << "[PhysicalLayer][Error] recv failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return NULL;
    }

    // Display the received data
    std::cout << "[PhysicalLayer] Received data: " << buff << std::endl;
    return buff;
}

PhysicalLayer::~PhysicalLayer() {
    // Clean up
    closesocket(sock);
    WSACleanup();
}

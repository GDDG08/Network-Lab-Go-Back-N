/*
 * @Project      :
 * @FilePath     : \Code\toolkit\debug.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 16:40:59
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-27 01:18:16
 */
#include "debug.hpp"

#include "..\network\physicalLayer.hpp"
#include "..\network\dataLinkLayer.hpp"
#include "..\network\networkLayer.hpp"

bool Debug::isEnabled = false;
std::string Debug::logFile = "";
std::ofstream Debug::logStream = std::ofstream();

void Debug::init(std::string hostname) {
    // logFile to be  hostname + current time formatted + log
    logFile = ".\\log\\" + hostname + "_" + std::to_string(time(nullptr)) + ".log";
    std::cout << "[Debug] logFile: " << logFile << std::endl;
    logStream.open(logFile);
    if (!logStream.is_open()) {
        std::cout << "[Debug] logStream open failed" << std::endl;
    } else {
        isEnabled = true;
    }
}

void Debug::logD(PhysicalLayer* pl, std::string msg) {
    if (!isEnabled)
        return;
    logStream << "[PhysicalLayer] " << msg << std::endl;
    logStream.flush();
}

void Debug::logD(DataLinkLayer* dll, std::string msg) {
    if (!isEnabled)
        return;

    logStream << "[DataLinkLayer] " << msg << std::endl;
    logStream.flush();
}

void Debug::logAT(DataLinkLayer* dll, int pdu_to_send, GBN_EVENT_TYPE statusCode) {
    if (!isEnabled)
        return;

    std::string status;
    switch (statusCode) {
        case GBN_EVENT_TYPE::NETWORK_LAYER_READY:
            status = "New";
            break;
        case GBN_EVENT_TYPE::TIMEOUT:
            status = "TO";
            break;
        case GBN_EVENT_TYPE::RESEND:
            status = "RT";
            break;
    }
    logStream << "[DataLinkLayer] TX\t"
              << dll->sendCount++ << ", pdu_to_send=" << pdu_to_send << ", status=" << status << ", ackedNo=" << int(dll->ack_expected) << std::endl;
    logStream.flush();
}

void Debug::logAR(DataLinkLayer* dll, int pdu_recv, std::string status) {
    if (!isEnabled)
        return;

    logStream << "[DataLinkLayer] RX\t"
              << dll->recvCount++ << ", pdu_exp=" << int(dll->frame_expected) << ", pdu_recv=" << pdu_recv << ", status=" << status << std::endl;
    logStream.flush();
}

void Debug::logD(NetworkLayer* nl, std::string msg) {
    if (!isEnabled)
        return;

    logStream << "[NetworkLayer] " << msg << std::endl;
    logStream.flush();
}

std::string
Debug::str2hex(const std::string& str) {
    std::stringstream ss;
    ss << std::uppercase << std::hex;

    for (int i = 0; i < str.size(); i++) {
        unsigned c = ((unsigned)str[i]) & 0xff;
        ss << std::setw(2) << std::setfill('0') << c;
    }
    return ss.str();
}

template <typename T>
std::string Debug::int2hex(T num) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setw(sizeof(T)) << std::setfill('0') << num;
    return ss.str();
}

template std::string Debug::int2hex<signed char>(signed char num);
template std::string Debug::int2hex<unsigned char>(unsigned char num);
template std::string Debug::int2hex<short>(short num);
template std::string Debug::int2hex<unsigned short>(unsigned short num);
template std::string Debug::int2hex<int>(int num);
template std::string Debug::int2hex<unsigned int>(unsigned int num);
template std::string Debug::int2hex<long>(long num);
template std::string Debug::int2hex<unsigned long>(unsigned long num);
template std::string Debug::int2hex<long long>(long long num);
template std::string Debug::int2hex<unsigned long long>(unsigned long long num);

/*
 * @Project      :
 * @FilePath     : \Code\toolkit\debug.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 16:40:59
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-27 18:15:57
 */
#include "debug.hpp"

#include "..\network\physicalLayer.hpp"
#include "..\network\dataLinkLayer.hpp"
#include "..\network\networkLayer.hpp"

bool Debug::isEnabled = false;
std::string Debug::logFile = "";
std::ofstream Debug::logStream = std::ofstream();

void Debug::init(std::string hostname) {
    // if .\\log\\ not exist, create it use windows
    if (_access(".\\log\\", 0) == -1) {
        std::cout << "[Debug] log dir not exist, create it" << std::endl;
        _mkdir(".\\log\\");
    }

    logFile = ".\\log\\" + hostname+ ".log";
    std::cout << "[Debug] logFile: " << logFile << std::endl;
    logStream.open(logFile);
    if (!logStream.is_open()) {
        std::cout << "[Debug] logStream open failed" << std::endl;
    } else {
        isEnabled = true;
        std::cout.rdbuf(nullptr);
    }
}

void Debug::logD(PhysicalLayer* pl, std::string msg) {
    if (!isEnabled)
        return;
    logStream << "[PhysicalLayer] " << msg << std::endl;
    logStream.flush();
    // std::cout << "[PhysicalLayer] " << msg << std::endl;
}

void Debug::logD(DataLinkLayer* dll, std::string msg) {
    if (!isEnabled)
        return;

    logStream << "[DataLinkLayer] " << msg << std::endl;
    logStream.flush();
    std::cout << "[DataLinkLayer] " << msg << std::endl;
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
        case GBN_EVENT_TYPE::CKSUM_ERR:
            status = "RT";
            break;
    }
    logStream << "[DataLinkLayer] TX\t"
              << dll->sendCount << ", pdu_to_send=" << pdu_to_send << ", status=" << status << ", ackedNo=" << int(dll->ack_expected) << std::endl;
    logStream.flush();

    std::cout << "[DataLinkLayer] TX\t"
              << dll->sendCount << ", pdu_to_send=" << pdu_to_send << ", status=" << status << ", ackedNo=" << int(dll->ack_expected) << std::endl;
}

void Debug::logAR(DataLinkLayer* dll, int pdu_recv, std::string status) {
    if (!isEnabled)
        return;

    logStream << "[DataLinkLayer] RX\t"
              << dll->recvCount << ", pdu_exp=" << int(dll->frame_expected) << ", pdu_recv=" << pdu_recv << ", status=" << status << std::endl;
    logStream.flush();
    std::cout << "[DataLinkLayer] RX\t"
              << dll->recvCount << ", pdu_exp=" << int(dll->frame_expected) << ", pdu_recv=" << pdu_recv << ", status=" << status << std::endl;
}

void Debug::logD(NetworkLayer* nl, std::string msg) {
    if (!isEnabled)
        return;

    logStream << "[NetworkLayer] " << msg << std::endl;
    logStream.flush();

    std::cout << "[NetworkLayer] " << msg << std::endl;
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

/*
 * @Project      :
 * @FilePath     : \Code\toolkit\debug.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 16:40:59
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 16:42:22
 */
#include "debug.hpp"

#include "..\network\physicalLayer.hpp"
#include "..\network\dataLinkLayer.hpp"
#include "..\network\networkLayer.hpp"

void Debug::logD(PhysicalLayer* pl, std::string msg) {
    std::cout << "[PhysicalLayer] " << msg << std::endl;
}

void Debug::logD(DataLinkLayer* dll, std::string msg) {
    std::cout << "[DataLinkLayer] " << msg << std::endl;
}

void Debug::logD(NetworkLayer* nl, std::string msg) {
    std::cout << "[NetworkLayer] " << msg << std::endl;
}

std::string
str2hex(const std::string& str) {
    std::stringstream ss;
    ss << std::uppercase << std::hex;

    for (int i = 0; i < str.size(); i++) {
        unsigned c = ((unsigned)str[i]) & 0xff;
        ss << std::setw(2) << std::setfill('0') << c;
    }
    return ss.str();
}

template <typename T>
std::string int2hex(T num) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setw(sizeof(T)) << std::setfill('0') << num;
    return ss.str();
}

template std::string int2hex<signed char>(signed char num);
template std::string int2hex<unsigned char>(unsigned char num);
template std::string int2hex<short>(short num);
template std::string int2hex<unsigned short>(unsigned short num);
template std::string int2hex<int>(int num);
template std::string int2hex<unsigned int>(unsigned int num);
template std::string int2hex<long>(long num);
template std::string int2hex<unsigned long>(unsigned long num);
template std::string int2hex<long long>(long long num);
template std::string int2hex<unsigned long long>(unsigned long long num);

/*
 * @Project      :
 * @FilePath     : \Code\network\Packet.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-23 14:21:36
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 15:56:05
 */
#ifndef PACKET_HPP
#define PACKET_HPP

#include <bitset>
#include <string>
#include <iostream>
#include "..\toolkit\debug.hpp"

// enum PACKET_TYPE
typedef enum {
    HELLO = 0,
    FILE_RQT = 1,
    FILE_BUF = 2,
    FILE_FIN = 3,
} PACKET_TYPE;

class Packet {
   public:
    PACKET_TYPE type = PACKET_TYPE::HELLO;
    std::string info = "";
    Packet(PACKET_TYPE type, std::string info)
        : type(type), info(info) {}

    Packet(std::string buff) {
        type = (PACKET_TYPE)buff[0];
        uint16_t len = (buff[1] << 8) | buff[2];
        info = buff.substr(3, len);
    }

    std::string to_buff() {
        std::string buff = "";

        uint16_t len = info.length();
        buff += (char)type;
        buff += (char)(len >> 8);
        buff += (char)(len & 0xff);
        buff += info;
        return buff;
    }
    void print() {
        std::cout << "Packet: type=" << type << " -->" << std::endl
                  << info << std::endl;
    }
};

#endif  // PACKET_HPP

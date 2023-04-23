/*
 * @Project      :
 * @FilePath     : \Code\network\Packet.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-23 14:21:36
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 14:23:44
 */
#ifndef PACKET_HPP
#define PACKET_HPP

#include <bitset>
#include <string>
#include <iostream>
#include "..\toolkit\debug.hpp"

// enum PACKET_TYPE
typedef enum PACKET_TYPE {
    HELLO = 0,
    FILE_RQT = 1,
    FILE_BUF = 2,
    FILE_END = 3,
} PACKET_TYPE;

class Packet {
   public:
    class Header {
       public:
        PACKET_TYPE type = PACKET_TYPE::HELLO;
        uint16_t len = 0;
        Header(PACKET_TYPE type, uint16_t len)
            : type(type), len(len) {}
        Header() {}
    };
    Header header;
    std::string info = "";
    Packet(PACKET_TYPE type, std::string info)
        : header(type, info.length()), info(info) {}
    Packet(std::string buff) {
        header.type = (PACKET_TYPE)buff[0];
        header.len = (buff[1] << 8) | buff[2];
        info = buff.substr(3, header.len);
    }

    std::string to_buff() {
        std::string buff = "";
        buff += (char)header.type;
        buff += (char)(header.len >> 8);
        buff += (char)(header.len & 0xff);
        buff += info;
        return buff;
    }
    void print() {
        std::cout << "Packet: type=" << header.type
                  << " len=" << header.len << std::endl;
    }
}

#endif  // PACKET_HPP

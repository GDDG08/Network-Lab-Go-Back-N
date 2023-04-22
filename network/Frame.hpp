/*
 * @Project      :
 * @FilePath     : \Code\network\Frame.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 17:05:53
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 03:32:05
 */
#ifndef FRAME_HPP
#define FRAME_HPP

#include <bitset>
#include <string>
#include <iostream>
#include "..\toolkit\checkCRC.hpp"
#include "..\toolkit\debug.hpp"

typedef enum FRAME_TYPE {
    DATA = 0,
    ACK = 1,
    NAK = 2,
    END = 3,
} FRAME_TYPE;

class Frame {
   public:
    // uint16_t len = 0;
    class Header {
       public:
        FRAME_TYPE type = FRAME_TYPE::END;
        uint8_t seq = 0;
        uint8_t ack = 0;
        Header(FRAME_TYPE type, uint8_t seq, uint8_t ack)
            : type(type), seq(seq), ack(ack) {}
        Header() {}
    };
    Header header;
    std::string info = "";
    uint16_t checksum = 0;

    Frame(FRAME_TYPE type, uint8_t seq, uint8_t ack, std::string info)
        : header(type, seq, ack), info(info) {
        std::string buff = to_buff_head() + info;
        checksum = CheckCRC::calc(buff);
    }

    // construct Frame from buff
    Frame(std::string buff) {
        header.type = (FRAME_TYPE)buff[0];
        header.seq = buff[1];
        header.ack = buff[2];
        uint16_t len = (buff[3] << 8) | buff[4];
        info = buff.substr(5, len);
        checksum = (buff[5 + len] << 8) | buff[6 + len];
    }

    // check checksum
    bool verify() {
        std::string buff = to_buff_head() + info;
        return CheckCRC::verify(buff, checksum);
    }

    Frame& operator=(const Frame& f) {
        this->header = f.header;
        this->info = f.info;
        this->checksum = f.checksum;
        return *this;
    }

    // convert Frame to buff to send
    std::string to_buff_head() {
        std::string buff;
        buff.resize(5);

        uint16_t len = info.length();
        buff[0] = header.type;
        buff[1] = header.seq;
        buff[2] = header.ack;
        buff[3] = (len >> 8) & 0xff;
        buff[4] = len & 0xff;
        return buff;
    }

    std::string to_buff_all() {
        std::string buff_head = to_buff_head();
        std::string buff;
        buff = buff_head + info;

        buff.resize(buff_head.length() + info.length() + 2);
        buff[buff.length() - 2] = (checksum >> 8) & 0xff;
        buff[buff.length() - 1] = checksum & 0xff;
        return buff;
    }

    // print Frame withour info
    void print() {
        std::cout << "Frame: type=" << header.type << " seq=" << (int)header.seq
                  << " ack=" << (int)header.ack << " len=" << info.length()
                  << " checksum=" << int2hex(checksum) << "[" << verify() << "]" << std::endl;
    }
};

#endif  // FRAME_HPP

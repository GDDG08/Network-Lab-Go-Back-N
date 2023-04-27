/*
 * @Project      :
 * @FilePath     : \Code\network\Packet.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-23 14:21:36
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 22:41:44
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
        uint16_t len = ((buff[1] & 0xff) << 8) | (buff[2] & 0xff);
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

class FileRequestInfo {
   public:
    unsigned long long fileID;
    unsigned long long fileSize;
    std::string filename;

    FileRequestInfo(unsigned long long fileID, unsigned long long fileSize, std::string filename)
        : filename(filename), fileSize(fileSize), fileID(fileID) {}

    FileRequestInfo(std::string buff) {
        const char* p = buff.c_str();
        memcpy(&fileID, p, 8);
        memcpy(&fileSize, p + 8, 8);
        uint16_t len = ((buff[16] & 0xff) << 8) | (buff[17] & 0xff);
        filename = buff.substr(18, len);
    }

    std::string to_buff() {
        char buff_c[18];
        memcpy(buff_c, &fileID, 8);
        memcpy(buff_c + 8, &fileSize, 8);

        uint16_t len = filename.length();
        buff_c[16] = (char)(len >> 8);
        buff_c[17] = (char)(len);
        return std::string(buff_c, 18) + filename;
    }
};
class FileBuffInfo {
   public:
    unsigned long long fileID;
    unsigned long long fileOffset;
    std::string data;
    // two constructors
    FileBuffInfo(unsigned long long fileID, unsigned long long fileOffset, const char* buff_c, int size)
        : fileOffset(fileOffset), fileID(fileID) {
        data = std::string(buff_c, size);
    }
    FileBuffInfo(std::string buff) {
        const char* p = buff.c_str();
        memcpy(&fileID, p, 8);
        memcpy(&fileOffset, p + 8, 8);
        uint16_t len = ((buff[16]& 0xff) << 8) | (buff[17]& 0xff);
        data = buff.substr(18, len);
    }
    std::string to_buff() {
        char buff_c[18];
        memcpy(buff_c, &fileID, 8);
        memcpy(buff_c + 8, &fileOffset, 8);

        uint16_t len = data.length();
        buff_c[16] = (char)(len >> 8);
        buff_c[17] = (char)(len);
        return std::string(buff_c, 18) + data;
    }
};

class FileFinishInfo {
   public:
    unsigned long long fileID;

    // two constructors
    FileFinishInfo(unsigned long long fileID)
        : fileID(fileID) {}
    FileFinishInfo(std::string buff) {
        const char* p = buff.c_str();
        memcpy(&fileID, p, 8);
    }
    std::string to_buff() {
        char buff_c[8];
        memcpy(buff_c, &fileID, 8);
        return std::string(buff_c, 8);
    }
};

#endif  // PACKET_HPP



#ifndef CHECKCRC_HPP
#define CHECKCRC_HPP

#include <string>
#include <bitset>

// use this file to generate checkbit using CRC-CCITT standard from Frame or buff
class CheckCRC {
   private:
    const static uint16_t crc_init = 0xffff;
    const static uint16_t poly = 0x1021;

   public:
    static uint16_t calc(std::string& buff) {
        uint16_t crc = crc_init;
        for (char byte : buff) {
            crc = (crc >> 8) | (crc << 8);
            crc ^= byte;
            crc ^= (crc & 0xff) >> 4;
            crc ^= crc << 12;
            crc ^= (crc & 0xff) << 5;
        }
        return crc;
    }

    // verify crc
    static bool verify(std::string& buff, uint16_t crc) {
        return calc(buff) == crc;
    }

};

#endif  // CHECKCRC_HPP

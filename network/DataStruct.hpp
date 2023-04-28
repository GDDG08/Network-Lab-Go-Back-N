/*
 * @Project      :
 * @FilePath     : \Code\network\DataStruct.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-26 17:17:43
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-28 15:58:38
 */
#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>

typedef struct {
    int port = -1;
    std::string addr = "255.255.255.255";
    std::string getStr() {
        return addr + ":" + std::to_string(port);
    }
} PhyAddrPort;

class RecvData {
   public:
    PhyAddrPort ap;
    std::string buff;
    RecvData(PhyAddrPort ap, const char* buff_c, int size)
        : ap(ap) {
        buff = std::string(buff_c, size);
    }
    RecvData(PhyAddrPort ap, std::string packet)
        : ap(ap), buff(packet) {
    }
    RecvData() {}
};

typedef enum { FRAME_ARRIVAL,
               CKSUM_ERR,
               TIMEOUT,
               NETWORK_LAYER_READY } GBN_EVENT_TYPE;

#endif  // DATASTRUCT_HPP

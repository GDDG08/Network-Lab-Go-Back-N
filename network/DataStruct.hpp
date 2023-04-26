/*
 * @Project      :
 * @FilePath     : \Codee:\@Document\课程活动\2022-2023-2\计算机网络\实验\Network Programming Projects\Project1\Code\network\DataStruct.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-26 17:17:43
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-27 01:00:11
 */
#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>


typedef struct {
    int port = 0;
    std::string addr = "255.255.255.255";
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
               RESEND,
               NETWORK_LAYER_READY } GBN_EVENT_TYPE;


#endif // DATASTRUCT_HPP

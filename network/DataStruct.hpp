/*
 * @Project      :
 * @FilePath     : \Code\network\DataStruct.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-26 17:17:43
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 17:17:49
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

#endif // DATASTRUCT_HPP

/*
 * @Project      :
 * @FilePath     : \Code\toolkit\debug.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 16:40:37
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 17:02:07
 */
#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>

class PhysicalLayer;
class DataLinkLayer;
class NetworkLayer;

class Debug {
   public:
    static void logD(PhysicalLayer *pl, std::string msg);
    static void logD(DataLinkLayer *dll, std::string msg);
    static void logD(NetworkLayer *nl, std::string msg);
    static void logD(std::string tag,std::string msg);
};

// PRINT HEX UTILS
std::string str2hex(const std::string& str);

template <typename T>
std::string int2hex(T num);
// {
//     std::stringstream ss;
//     ss << std::hex << std::uppercase << std::setw(sizeof(T)) << std::setfill('0') << num;
//     return ss.str();
// }

#endif  // DEBUG_HPP

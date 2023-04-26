/*
 * @Project      :
 * @FilePath     : \Codee:\@Document\课程活动\2022-2023-2\计算机网络\实验\Network Programming Projects\Project1\Code\toolkit\debug.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 16:40:37
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-27 01:08:46
 */
#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>
#include <bitset>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "..\network\DataStruct.hpp"

class PhysicalLayer;
class DataLinkLayer;
class NetworkLayer;

class Debug {
   private:
    static bool isEnabled;
    static std::string logFile;
    static std::ofstream logStream;

   public:
    static void init(std::string hostname);
    static void logD(PhysicalLayer* pl, std::string msg);
    static void logD(DataLinkLayer* dll, std::string msg);
    static void logAT(DataLinkLayer* dll, int pdu_to_send, GBN_EVENT_TYPE status);
    static void logAR(DataLinkLayer* dll, int pdu_recv, std::string status);
    static void logD(NetworkLayer* nl, std::string msg);
    static void logD(std::string tag, std::string msg);

    // PRINT HEX UTILS
    static std::string str2hex(const std::string& str);

    template <typename T>
    static std::string int2hex(T num);
    // {
    //     std::stringstream ss;
    //     ss << std::hex << std::uppercase << std::setw(sizeof(T)) << std::setfill('0') << num;
    //     return ss.str();
    // }
};

#endif  // DEBUG_HPP

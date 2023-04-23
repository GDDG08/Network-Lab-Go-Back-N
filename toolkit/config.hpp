/*
 * @Project      :
 * @FilePath     : \Code\toolkit\config.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 18:45:41
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 19:01:43
 */
#ifndef CONFIG_HPP
#define CONFIG_HPP


#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using json = nlohmann::json;

class Config {
   private:
    string path;

    json readConfigFile();

   public:
    class ConfigBean {
       public:
        int udpPort;
        int dataSize;
        int errorRate;
        int lostRate;
        int swSize;
        int initSeqNo;
        int timeout;
        std::string savePath;

        void printConfig() {
            cout << "======== Config ========" << endl;
            cout << "UDPPort: " << udpPort << endl;
            cout << "DataSize: " << dataSize << endl;
            cout << "ErrorRate: " << errorRate << endl;
            cout << "LostRate: " << lostRate << endl;
            cout << "SWSize: " << swSize << endl;
            cout << "InitSeqNo: " << initSeqNo << endl;
            cout << "Timeout: " << timeout << endl;
            cout << "SavePath: " << savePath << endl;
            cout << "========================" << endl;
        }
    };
    Config(string path);

    ConfigBean parseConfig();
};
#endif // CONFIG_HPP

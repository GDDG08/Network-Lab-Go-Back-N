/*
 * @Project      :
 * @FilePath     : \Code\toolkit\config.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 18:45:33
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 18:57:58
 */
#include "config.hpp"

Config::Config(string path){
    this->path = path;
}

// read Config File
json Config::readConfigFile() {
    ifstream ifs(path);
    json j;
    ifs >> j;
    return j;
}

Config::ConfigBean Config::parseConfig() {
    json j = readConfigFile();
    ConfigBean cb;
    cb.udpPort = j["UDPPort"];
    cb.dataSize = j["DataSize"];
    cb.errorRate = j["ErrorRate"];
    cb.lostRate = j["LostRate"];
    cb.swSize = j["SWSize"];
    cb.initSeqNo = j["InitSeqNo"];
    cb.timeout = j["Timeout"];
    cb.savePath = j["SavePath"];

    return cb;
}
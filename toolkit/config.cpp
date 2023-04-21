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

ConfigBean Config::parseConfig() {
    json j = readConfigFile(path);
    ConfigBean cb;
    cb.UDPPort = j["UDPPort"];
    cb.error_rate = j["error_rate"];
    cb.lost_rate = j["lost_rate"];
    cb.SW_size = j["SW_size"];
    cb.time_out = j["time_out"];
    cb.data_size = j["data_size"];
    cb.init_seq_no = j["init_seq_no"];
    return cb;
}
/*
 * @Project      :
 * @FilePath     : \Code\toolkit\config.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 18:45:41
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 19:01:43
 */

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
        int UDPPort;
        int error_rate;
        int lost_rate;
        int SW_size;
        int time_out;
        int data_size;
        int init_seq_no;
    };
    Config(string path);

    ConfigBean parseConfig();
};
/*
 * @Project      :
 * @FilePath     : \Code\testTerminal.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:58:20
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 20:07:00
 */

#include <iostream>
#include <string>
using namespace std;

#include "network\physicalLayer.hpp"
#include "toolkit\config.hpp"

#ifndef HOST_ID
#define HOST_ID "null"
#endif

int main() {
    printf("[TestTerminal] ID-> " HOST_ID "\n");

    Config config("config_host_" HOST_ID ".json");
    Config::ConfigBean cfg = config.parseConfig();
    cfg.printConfig();

    int PORT_TEST = 0;
    if (cfg.udpPort == 12345) {
        PORT_TEST = 12346;
    } else {
        PORT_TEST = 12345;
    }

    PhysicalLayer pl(cfg.udpPort);
    pl.init();

    pl.startRecvTask();

    while (true) {
        // pause in cmd
        cout << "Press any key to continue..." << endl;
        getchar();

        pl.sendData("Hello World!", PORT_TEST, inet_addr("127.0.0.1"));
    }
    return 0;
}
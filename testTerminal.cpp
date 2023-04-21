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

// #if HOST_ID == A
// #define HOST_PORT 11111
// #elif HOST_ID == B
// #define HOST_PORT 11112
// #elif HOST_ID == C
// #define HOST_PORT 11113
// #endif

int main() {
    printf("[TestTerminal] ID-> " HOST_ID "\n");
    Config config("config_host_" HOST_ID ".json");
    Config::ConfigBean cfg = config.parseConfig();

    PhysicalLayer pl(cfg.UDPPort);
    pl.init();

    // pause in cmd
    cout << "Press any key to continue..." << endl;
    getchar();

    pl.sendData("Hello World!", 11112, inet_addr("127.0.0.1"));
    cout << "Hello World!" << endl;
    return 0;
}
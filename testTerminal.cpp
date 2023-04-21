/*
 * @Project      :
 * @FilePath     : \Code\testTerminal.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:58:20
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 19:03:40
 */

#include <iostream>
#include <string>
using namespace std;

#include "network\physicalLayer.hpp"
#include "toolkit\config.hpp"

#define HOST_ID A

#if HOST_ID == A
#define HOST_PORT 11111
#elif HOST_ID == B
#define HOST_PORT 11112
#elif HOST_ID == C
#define HOST_PORT 11113
#endif

int main() {
    Config config("config_host1.json");
    ConfigBean cfg = config.parseConfig();

        PhysicalLayer pl(HOST_PORT);
    pl.init();

    // pause in cmd
    cout << "Press any key to continue..." << endl;
    getchar();

    pl.sendData("Hello World!", 11112, inet_addr("127.0.0.1"));
    cout << "Hello World!" << endl;
    return 0;
}
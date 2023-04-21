/*
 * @Project      :
 * @FilePath     : \Code\testTerminal2.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:58:20
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-21 19:09:32
 */

#include <iostream>
#include <string>
using namespace std;

#include "network\physicalLayer.hpp"

#define HOST_A 1
#define HOST_B 2
#define HOST_C 3
#define HOST_ID HOST_B

#if HOST_ID == HOST_A
#define HOST_PORT 11111
#elif HOST_ID == HOST_B
#define HOST_PORT 11112
#elif HOST_ID == HOST_C
#define HOST_PORT 11113
#endif

int main() {
    PhysicalLayer pl(HOST_PORT);
    pl.init();

    // pause in cmd
    cout << "Press any key to continue..." << endl;
    getchar();

    string data = pl.recvData();
    cout << data << endl;
    return 0;
}
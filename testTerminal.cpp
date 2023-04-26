/*
 * @Project      :
 * @FilePath     : \Code\testTerminal.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:58:20
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 15:47:10
 */

#include <iostream>
#include <string>
using namespace std;

#include "network\physicalLayer.hpp"
#include "network\dataLinkLayer.hpp"
#include "network\networkLayer.hpp"
#include "toolkit\config.hpp"
#include "toolkit\checkCRC.hpp"
#include "toolkit\debug.hpp"

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

    // PhysicalLayer pl(cfg);
    // pl.init();

    // pl.startRecvTask();

    // // test CheckCRC.calc()
    // string test = "Hello World!";
    // Frame tf(FRAME_TYPE::DATA, 0, 0, test);
    // tf.print();

    // cout << "Buff " << str2hex(tf.to_buff_all()) << endl;

    // while (true) {
    //     // pause in cmd
    //     cout << "Press any key to continue..." << endl;
    //     getchar();

    //     pl.sendData("Hello World!", {PORT_TEST, "127.0.0.1"});
    // }

    DataLinkLayer dll(cfg);
    dll.init();

    // dll.test_timer();
    // use two threads ad producer and consumer to test BlockingQueue

    // test BlockingQueue
    // mutex tm;
    // BlockingQueue<int> bq(10);
    // std::thread producer([&bq, &tm]() {
    //     for (int i = 0; i < 30; i++) {
    //         tm.lock();
    //         cout << "=======: " << i << endl;
    //         tm.unlock();
    //         bq.put(i);
    //         std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //     }
    // });
    // std::thread consumer([&bq, &tm]() {
    //     for (int i = 0; i < 30; i++) {
    //         int g = bq.get();
    //             tm.lock();
    //         cout << "@@: " << g << endl;
    //         tm.unlock();
    //         std::this_thread::sleep_for(std::chrono::milliseconds(200));
    //     }
    // });
    // producer.join();
    // consumer.join();
    // uint16_t len = 0xF234;
    // std::string buff = "";
    // buff += (len >> 8);
    // buff += len;
    // cout << str2hex(buff) << endl;
    // uint16_t len2 = (buff[0] << 8) | buff[1];
    // cout << int2hex(len2) << endl;

    // NetworkLayer nl(cfg);
    // nl.init();
    while (true) {
        // pause in cmd
        cout << "Press any key to continue..." << endl;
        getchar();

        // nl.dataLinkLayer->onNetworkLayerTx(PhyAddrPort{PORT_TEST, "127.0.0.1"}, Packet(PACKET_TYPE::HELLO, "Hello World!").to_buff());
        // nl.sendHello(PhyAddrPort{PORT_TEST, "127.0.0.1"});
        // nl.sendFile(PhyAddrPort{PORT_TEST, "127.0.0.1"}, "test.txt");

        // test ack piggyback

        // dll.onNetworkLayerTx(PhyAddrPort{PORT_TEST, "127.0.0.1"}, Packet(PACKET_TYPE::HELLO, "Hello World!").to_buff());
        dll.testDLL(PhyAddrPort{PORT_TEST, "127.0.0.1"});
    }
}
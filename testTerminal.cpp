/*
 * @Project      :
 * @FilePath     : \Code\testTerminal.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-21 14:58:20
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-29 02:36:36
 */

#include <iostream>
#include <string>
using namespace std;

#include "toolkit\config.hpp"
#include "toolkit\checkCRC.hpp"
#include "toolkit\debug.hpp"
#include "network\physicalLayer.hpp"
#include "network\dataLinkLayer.hpp"
#include "network\networkLayer.hpp"

#ifndef HOST_ID
#define HOST_ID "null"
#endif

int main() {
    printf("[TestTerminal] ID-> " HOST_ID "\n");

    Config config("config_host_" HOST_ID ".json");
    Config::ConfigBean cfg = config.parseConfig();
    cfg.printConfig();

    int PORT_TEST = 0;
    std::string ADDR_TEST = "127.0.0.1";
    if (cfg.udpPort == 12345) {
        PORT_TEST = 12346;
        // ADDR_TEST = "192.168.37.250";
    } else {
        PORT_TEST = 12345;
        // ADDR_TEST = "192.168.37.100";
    }

    Debug::init("GBN_" HOST_ID);

    // PhysicalLayer pl(cfg);
    // pl.init();

    // pl.startRecvTask();

    // // test CheckCRC.calc()
    // string test = "Hello World!";
    // Frame tf(FRAME_TYPE::DATA, 0, 0, test);
    // tf.print();

    // cout << "Buff " << Debug::str2hex(tf.to_buff_all()) << endl;

    // cout << "Press any key to continue..." << endl;
    // getchar();

    // DataLinkLayer dll(cfg);
    // dll.init();

    // cout << "Press any key to continue..." << endl;
    // auto time =  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    // cout << time << endl;
    // while (true) {
    //     //     // pause in cmd
    //     // cout << "Press any key to continue..." << endl;
    //     getchar();
    //     for (int i = 0; i < 1000; i++) {
    //         dll.onNetworkLayerTx({PORT_TEST, "127.0.0.1"}, "01234567890");
    //     }

    //     // pl.sendData("Hello World!", {PORT_TEST, "127.0.0.1"}, true);
    //     // dll.onNetworkLayerTx({PORT_TEST, "127.0.0.1"}, "01234567890");
    // }

    // std::thread test1([&pl, PORT_TEST]() {
    //     while (true) {
    //         pl.sendData("Hello World!", {PORT_TEST, "127.0.0.1"});
    //     }
    // });
    // std::thread test2([&pl, PORT_TEST]() {
    //     while (true) {
    //         pl.sendData("AABBCC", {PORT_TEST, "127.0.0.1"});
    //     }
    // });

    // cout << "Press any key to continue..." << endl;
    // getchar();

    // test1.detach();
    // test2.detach();

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
    // cout << Debug::str2hex(buff) << endl;
    // uint16_t len2 = (buff[0] << 8) | buff[1];
    // cout << Debug::int2hex(len2) << endl;

    NetworkLayer nl(cfg);
    nl.init();

    // std::string buff;
    // buff.resize(2);
    // buff[0] = 0x01;
    // buff[1] = 0xEF;
    // uint16_t len = (buff[0] << 8) | buff[1] ;
    // len = (buff[0] << 8) | (buff[1] & 0xff);

    // pause for 3 seconds
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // while (true) {
    //     // pause in cmd
    //     cout << "Press any key to continue..." << endl;
    getchar();

    // nl.dataLinkLayer->onNetworkLayerTx(PhyAddrPort{PORT_TEST, "127.0.0.1"}, Packet(PACKET_TYPE::HELLO, "Hello World!").to_buff());
    // nl.sendHello(PhyAddrPort{PORT_TEST, "127.0.0.1"});
    // nl.sendFile(PhyAddrPort{PORT_TEST, "127.0.0.1"}, "test2.txt");
    // nl.sendFile(PhyAddrPort{PORT_TEST, "127.0.0.1"}, "GBN_Network1.exe");
    nl.sendFile(PhyAddrPort{PORT_TEST, "127.0.0.1"}, "test3.txt");
    nl.sendFile(PhyAddrPort{PORT_TEST, "127.0.0.1"}, "test4.txt");
    // nl.sendFile(PhyAddrPort{PORT_TEST, ADDR_TEST}, "test5.txt");

    // test ack piggyback

    // dll.onNetworkLayerTx(PhyAddrPort{PORT_TEST, "127.0.0.1"}, Packet(PACKET_TYPE::HELLO, "Hello World!").to_buff());
    // dll.testDLL(PhyAddrPort{PORT_TEST, "127.0.0.1"});

    // Todo：nbuffer诈尸事件，ACK不死事件
    // }
    getchar();
    return 0;
}
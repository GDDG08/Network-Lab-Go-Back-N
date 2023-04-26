/*
 * @Project      :
 * @FilePath     : \Code\network\networkLayer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 12:33:33
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 17:15:05
 */

#ifndef NETWORKLAYER_HPP
#define NETWORKLAYER_HPP

#include <iostream>
#include <thread>
#include <sys/stat.h>
#include "..\toolkit\msgQueue.hpp"
#include "..\toolkit\config.hpp"
#include "Packet.hpp"
#include "DataStruct.hpp"


class DataLinkLayer;
class RecvData;

typedef BlockingQueue<RecvData> PacketQueue;

typedef struct {
    unsigned long long fileID;
    unsigned long long fileSize;
    std::string filename;
    PhyAddrPort ap;
} FileInfo;

class NetworkLayer {
   private:
    Config::ConfigBean cfg;
    PacketQueue* packetQueue;
    DataLinkLayer* dataLinkLayer;

    bool isRunning;
    std::thread packetHandler;

    std::map<unsigned long long, FileInfo> filesMap;
    const static int FILE_FRAME_SIZE = 512;
    unsigned long long FileID = 0;
    void handlePackets();

   public:
    NetworkLayer(Config::ConfigBean cfg);
    ~NetworkLayer();
    int sendFile(PhyAddrPort ap, std::string path);
    int sendHello(PhyAddrPort ap);
    static void onDataLinkLayerRx(void*, RecvData data);

    void init();
};

#endif  // NETWORKLAYER_HPP

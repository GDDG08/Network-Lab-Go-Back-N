/*
 * @Project      :
 * @FilePath     : \Codee:\@Document\课程活动\2022-2023-2\计算机网络\实验\Network Programming Projects\Project1\Code\network\networkLayer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 12:33:33
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-28 16:37:27
 */

#ifndef NETWORKLAYER_HPP
#define NETWORKLAYER_HPP

#include <iostream>
#include <thread>
#include <sys/stat.h>
#include <io.h>
#include <direct.h>
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
    friend class Debug;

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
    void onDataLinkLayerRx(RecvData data);

    void init();
};

#endif  // NETWORKLAYER_HPP

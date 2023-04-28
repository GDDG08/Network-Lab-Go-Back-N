'''
Project      :
FilePath     : \Code\bin\test.py
Descripttion :
Author       : GDDG08
Date         : 2023-04-28 21:20:18
LastEditors  : GDDG08
LastEditTime : 2023-04-29 00:00:22
'''
#  python to test bin/GBN_Network1.exe
import time
import datetime
import os
import json

# change config
default_config = {
    "UDPPort": 12345,
    "DataSize": 512,
    "ErrorRate": 5,
    "LostRate": 5,
    "OnDebug": True,
    "SWSize": 7,
    "InitSeqNo": 0,
    "Timeout": 200,
    "SavePath": ".\\recv1\\"
}

default_config2 = {
    "UDPPort": 12346,
    "DataSize": 512,
    "ErrorRate": 5,
    "LostRate": 5,
    "OnDebug": True,
    "SWSize": 7,
    "InitSeqNo": 0,
    "Timeout": 200,
    "SavePath": ".\\recv2\\"
}


def writeConfig(DataSize=512, ErrorRate=5, LostRate=5, SWSize=7, Timeout=200):
    config = default_config
    config["DataSize"] = DataSize
    config["ErrorRate"] = ErrorRate
    config["LostRate"] = LostRate
    config["SWSize"] = SWSize
    config["Timeout"] = Timeout
    with open("config_host_1.json", "w") as f:
        f.write(json.dumps(config))


def writeConfig2(DataSize=512, ErrorRate=5, LostRate=5, SWSize=7, Timeout=200):
    config = default_config2
    config["DataSize"] = DataSize
    config["ErrorRate"] = ErrorRate
    config["LostRate"] = LostRate
    config["SWSize"] = SWSize
    config["Timeout"] = Timeout
    with open("config_host_2.json", "w") as f:
        f.write(json.dumps(config))


_DataSize = 512
_ErrorRate = 5
_LostRate = 5
_SWSize = 7
_Timeout = 200


def TEST():
    os.system("..\\recompile.bat")
    writeConfig(DataSize=_DataSize, ErrorRate=_ErrorRate, LostRate=_LostRate, SWSize=_SWSize, Timeout=_Timeout)
    # get time in ms

    time0 = time.time()

    os.system("start GBN_Network1.exe")
    os.system("GBN_Network2.exe")
    time1 = time.time()
    # os.system("bin\GBN_Network2.exe")
    # print("RUN!")
    logF = ""
    with open(file=f"log\\GBN_1_{_DataSize}_{_ErrorRate}_{_LostRate}_{_SWSize}_{_Timeout}.log", mode="r") as f:
        logF = f.read()

    # find last "[DataLinkLayer] RX	"in logF
    RX0 = logF.rfind("[DataLinkLayer] TX")+18
    RX1 = logF[RX0:].find(",")
    # print(RX0)
    # print(RX1)
    RXNUM = logF[RX0:RX0+RX1].strip()
    print(RXNUM)

    with open("testresult.txt", mode="a+") as f:
        f.write(f"{_DataSize}_{_ErrorRate}_{_LostRate}_{_SWSize}_{_Timeout} ={RXNUM} @ {time1-time0-2}\n")


def TEST2():
    os.system("..\\recompile.bat")
    writeConfig(DataSize=_DataSize, ErrorRate=_ErrorRate, LostRate=_LostRate, SWSize=_SWSize, Timeout=_Timeout)
    writeConfig2(DataSize=_DataSize, ErrorRate=_ErrorRate, LostRate=_LostRate, SWSize=_SWSize, Timeout=_Timeout)

    # get time in ms

    time0 = time.time()

    os.system("start GBN_Network1.exe")
    os.system("GBN_Network2.exe")
    time1 = time.time()
    # os.system("bin\GBN_Network2.exe")
    # print("RUN!")
    logF = ""
    with open(file=f"log\\GBN_1_{_DataSize}_{_ErrorRate}_{_LostRate}_{_SWSize}_{_Timeout}.log", mode="r") as f:
        logF = f.read()

    # find last "[DataLinkLayer] RX	"in logF
    RX0 = logF.rfind("[DataLinkLayer] TX")+18
    RX1 = logF[RX0:].find(",")
    # print(RX0)
    # print(RX1)
    RXNUM = logF[RX0:RX0+RX1].strip()
    print(RXNUM)

    with open("testresult.txt", mode="a+") as f:
        f.write(f"{_DataSize}_{_ErrorRate}_{_LostRate}_{_SWSize}_{_Timeout} ={RXNUM} @ {time1-time0-2}\n")
# TEST()


# exit()
# _ErrorRate = 0
# _LostRate = 0

# for i in range(448, 1280, 32):
#     _DataSize = i
#     TEST()
# for i in range(1280, 4097, 256):
#     _DataSize = i
#     TEST()

# _DataSize = 512
# _LostRate = 5
# _ErrorRate = 5

for i in range(1, 15,1):
    _SWSize = i
    TEST2()
for i in range(15, 127,8):
    _SWSize = i
    TEST2()
_SWSize = 7

# for i in range(0, 30, 1):
#     _ErrorRate = i
#     TEST()
# _ErrorRate = 0
# for i in range(20, 31, 1):
#     _LostRate = i
#     TEST()
# _LostRate = 5
# _ErrorRate = 5

# for i in range(1100, 2001, 100):
#     _Timeout = i
#     TEST()
# _Timeout = 200
# wait until the exe print "recv over"

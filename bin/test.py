'''
Project      :
FilePath     : \Code\bin\test.py
Descripttion :
Author       : GDDG08
Date         : 2023-04-28 21:20:18
LastEditors  : GDDG08
LastEditTime : 2023-04-28 21:58:52
'''
#  python to test bin/GBN_Network1.exe
import time
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


def writeConfig(DataSize=512, ErrorRate=5, LostRate=5, SWSize=7, Timeout=200):
    config = default_config
    config["DataSize"] = DataSize
    config["ErrorRate"] = ErrorRate
    config["LostRate"] = LostRate
    config["SWSize"] = SWSize
    config["Timeout"] = Timeout
    with open("config_host_1.json", "w") as f:
        f.write(json.dumps(config))


DataSize = 512
ErrorRate = 5
LostRate = 5
SWSize = 7
Timeout = 200

for i in range(1, 2, 32):
    os.system("..\\recompile.bat")
    writeConfig(DataSize=512)
    # get time now

    time0 = time.localtime()

    os.system("start GBN_Network1.exe")
    os.system("GBN_Network2.exe")
    # os.system("bin\GBN_Network2.exe")
    # print("RUN!")
    logF = ""
    with open(file=f"log\\GBN_1_{DataSize}_{ErrorRate}_{LostRate}_{SWSize}_{Timeout}.log", mode="r") as f:
        logF = f.read()

    # find last "[DataLinkLayer] RX	"in logF
    RX0 = logF.rfind("[DataLinkLayer] RX")+18
    RX1 = logF[RX0:].find(",")
    # print(RX0)
    # print(RX1)
    RXNUM = logF[RX0:RX0+RX1].strip()
    print(RXNUM)

    with  open(testresult.txt, mode="a") as f:
        f.write(f"{DataSize}_{ErrorRate}_{LostRate}_{SWSize}_{Timeout}  {RXNUM}")


# wait until the exe print "recv over"

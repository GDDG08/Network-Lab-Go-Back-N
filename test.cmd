REM Path: testTerminal.cmd
REM compile use g++ for physicalLayer.cpp physicalLayer.hpp and testTerminal.cpp, first .o and link to .exe
REM run testTerminal.exe and testTerminal2.exe

g++ -c physicalLayer.cpp -o physicalLayer.o 
g++ -c physicalLayer.cpp -o physicalLayer.o 
g++ -c testTerminal.cpp -o testTerminal.o
g++ -c testTerminal2.cpp -o testTerminal2.o
g++ physicalLayer.o testTerminal.o -o testTerminal.exe -lwsock32
g++ physicalLayer.o testTerminal2.o -o testTerminal2.exe -lwsock32


@REM start testTerminal.exe
@REM start testTerminal2.exe


/*
 * @Project      :
 * @FilePath     : \Code\toolkit\testClassB.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-26 15:39:17
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 15:48:20
 */
#include "testClassB.hpp"

void TestClassB::callA() {
    std::cout << "TestClassB::callA()" << std::endl;
    a->callA();
}

void TestClassB::callB() {
    std::cout << "TestClassB::callB()" << std::endl;
}

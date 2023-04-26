/*
 * @Project      :
 * @FilePath     : \Code\toolkit\testClassA.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-26 15:39:06
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 15:50:31
 */
#include "testClassA.hpp"

void TestClassA::callA() {
    std::cout << "TestClassA::callA()" << std::endl;
}

void TestClassA::callB() {
    std::cout << "TestClassA::callB()" << std::endl;
    TestClassB b(this);
    b.callA();
}
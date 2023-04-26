/*
 * @Project      :
 * @FilePath     : \Code\testClassA.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-26 15:39:26
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 15:39:49
 */
#ifndef TESTCLASSA_HPP
#define TESTCLASSA_HPP

#include <iostream>
#include "testClassB.hpp"

class TestClassA {
   public:
    TestClassA(){};
    ~TestClassA(){};

    void callA();
    void callB();
};

#endif  // TESTCLASSA_HPP

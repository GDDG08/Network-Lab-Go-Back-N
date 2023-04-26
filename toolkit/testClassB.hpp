/*
 * @Project      : 
 * @FilePath     : \Code\testClassB.hpp
 * @Descripttion : 
 * @Author       : GDDG08
 * @Date         : 2023-04-26 15:39:34
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-26 15:39:40
 */

#ifndef TESTCLASSB_HPP
#define TESTCLASSB_HPP

#include <iostream>
#include "testClassA.hpp"

class TestClassA;

class TestClassB {
    private:   
    TestClassA *a;
   public:
    TestClassB(TestClassA *a) : a(a){};
    ~TestClassB(){};

    void callA();
    void callB();
};

#endif  // TESTCLASSB_HPP

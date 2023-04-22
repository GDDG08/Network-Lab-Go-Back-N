/*
 * @Project      :
 * @FilePath     : \Code\toolkit\debug.cpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 16:40:59
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-22 18:41:17
 */
#include "debug.hpp"

std::string str2hex(const std::string& str) {
    std::stringstream ss;
    ss << std::uppercase << std::hex;

    for (int i = 0; i < str.size(); i++) {
        unsigned c = ((unsigned)str[i]) & 0xff;
        ss << c;
    }
    return ss.str();
}

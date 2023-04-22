/*
 * @Project      :
 * @FilePath     : \Code\toolkit\Timer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-23 01:06:05
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 01:23:27
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <thread>
#include <functional>

// Timer to call fuction after a period of time, setTimeout
class Timer {
   private:
    std::thread timerThread;
    bool isRunning = false;
    int duration;
    std::function<void()> callback;
    void sleepAndRun() {
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        if (isRunning) {
            callback();
        }
    }

   public:
    Timer() {}
    Timer(std::function<void()> callback, int duration) {
        this->callback = callback;
        this->duration = duration;
    }
    void start(bool async = true) {
        if (isRunning)
            return;
        isRunning = true;
        if (async) {
            timerThread = std::thread(&Timer::sleepAndRun, this);
        } else {
            sleepAndRun();
        }
    }
    void stop() {
        isRunning = false;
        timerThread.detach();
    }
    ~Timer() {
        stop();
    }
};

#endif  // TIMER_HPP

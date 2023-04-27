/*
 * @Project      :
 * @FilePath     : \Code\toolkit\Timer.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-23 01:06:05
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-27 23:51:47
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
    // get current time in ms
    long long startTime;

    int duration;
    std::function<void()> callback;
    void sleepAndRun(long long threadTime) {
        // while (getTime() - startTime < duration) {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // }
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        if (isRunning && (threadTime == startTime)) {
            callback();
        }
    }

    long long getTime() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

   public:
    Timer() {}
    Timer(std::function<void()> callback, int duration) {
        this->callback = callback;
        this->duration = duration;
    }
    void start() {
        if (isRunning)
            return;
        isRunning = true;
        startTime = getTime();
        timerThread = std::thread(&Timer::sleepAndRun, this, startTime);
        timerThread.detach();
    }
    void stop() {
        isRunning = false;
        // if (timerThread.joinable()) {
        //     timerThread.detach();
        // }
    }
    ~Timer() {
        stop();
    }
};

#endif  // TIMER_HPP

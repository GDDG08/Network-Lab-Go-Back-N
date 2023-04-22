/*
 * @Project      :
 * @FilePath     : \Code\toolkit\msgQueue.hpp
 * @Descripttion :
 * @Author       : GDDG08
 * @Date         : 2023-04-22 21:39:24
 * @LastEditors  : GDDG08
 * @LastEditTime : 2023-04-23 02:17:34
 */
#ifndef MSGQUEUE_HPP
#define MSGQUEUE_HPP

#include <condition_variable>
#include <deque>
#include <mutex>
// #include "..\network\physicalLayer.hpp"

template <typename T>
class BlockingQueue {
   private:
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    std::deque<T> queue_;
    unsigned size_ = 0;

   public:
    BlockingQueue(unsigned size)
        : size_(size) {}
    BlockingQueue() {}

    // put but wait if no space
    void put(const T x) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (size_ != 0 && queue_.size() > size_) {
            not_full_.wait(lock);
        }
        queue_.push_back(std::move(x));
        not_empty_.notify_one();
    }

    T get() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            not_empty_.wait(lock);
        }
        const T front = queue_.front();
        queue_.pop_front();
        not_full_.notify_one();
        return front;
    }

    unsigned size() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.size();
    }
};

// typedef BlockingQueue<RecvData> RxDataQueue;
#endif
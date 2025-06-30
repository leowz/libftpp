#ifndef THREAD_SAFE_BLOCKING_QUEUE_HPP
# define THREAD_SAFE_BLOCKING_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

template<typename T>
class ThreadSafeBlockingQueue
{
public:
	ThreadSafeBlockingQueue(): stopped_(false) {};
	~ThreadSafeBlockingQueue() = default;
    
    // Disable copy
    ThreadSafeBlockingQueue(const ThreadSafeBlockingQueue&) = delete;
    ThreadSafeBlockingQueue& operator=(const ThreadSafeBlockingQueue&) = delete;

	void    push_back(const T& item) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            if (stopped_) throw std::runtime_error("Queue stopped");
            queue_.push_back(item);
        }
        // notification happens **after** unlock
        condVar_.notify_one();
    };

	void    push_front(T&& item) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            if (stopped_) throw std::runtime_error("Queue stopped");
            queue_.push(std::move(item));
        }
        condVar_.notify_one();
    };

	T   pop_back() {
        std::unique_lock<std::mutex> lock(mutex_);
        condVar_.wait(lock, [this] { return !queue_.empty() || stopped_; });
        if (stopped_ && queue_.empty()) throw std::runtime_error("Queue stopped");
        T item = std::move(queue_.back());
        queue_.pop_back();
        return item;
    };

	T   pop_front() {
        std::unique_lock<std::mutex> lock(mutex_);
        condVar_.wait(lock, [this] { return !queue_.empty() || stopped_; });
        if (stopped_ && queue_.empty()) throw std::runtime_error("Queue stopped");
        T item = std::move(queue_.front());
        queue_.pop_front();
        return item;
    };

    void stop() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            stopped_ = true;
        }
        condVar_.notify_all();
    }

private:
	std::deque<T> queue_;
	std::mutex mutex_;
	std::condition_variable condVar_;
    bool stopped_;
};

#endif
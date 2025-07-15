#ifndef THREAD_SAFE_BLOCKING_QUEUE_TPP
#define THREAD_SAFE_BLOCKING_QUEUE_TPP

template<typename T>
ThreadSafeBlockingQueue<T>::ThreadSafeBlockingQueue(): stopped_(false) {};

template<typename T>
ThreadSafeBlockingQueue<T>::~ThreadSafeBlockingQueue() {};

template<typename T>
void    ThreadSafeBlockingQueue<T>::push_back(const T& item) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (stopped_) throw std::runtime_error("Queue stopped");
        queue_.push_back(item);
    }
    // notification happens **after** unlock
    condVar_.notify_one();
};

template<typename T>
void    ThreadSafeBlockingQueue<T>::push_front(T&& item) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (stopped_) throw std::runtime_error("Queue stopped");
        queue_.push(std::move(item));
    }
    condVar_.notify_one();
};

template<typename T>
T   ThreadSafeBlockingQueue<T>::pop_back() {
    std::unique_lock<std::mutex> lock(mutex_);
    condVar_.wait(lock, [this] { return !queue_.empty() || stopped_; });
    if (stopped_ && queue_.empty()) throw std::runtime_error("Queue stopped");
    T item = std::move(queue_.back());
    queue_.pop_back();
    return item;
};

template<typename T>
T   ThreadSafeBlockingQueue<T>::pop_front() {
    std::unique_lock<std::mutex> lock(mutex_);
    condVar_.wait(lock, [this] { return !queue_.empty() || stopped_; });
    if (stopped_ && queue_.empty()) throw std::runtime_error("Queue stopped");
    T item = std::move(queue_.front());
    queue_.pop_front();
    return item;
};

template<typename T>
void ThreadSafeBlockingQueue<T>::stop() {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        stopped_ = true;
    }
    condVar_.notify_all();
}

#endif
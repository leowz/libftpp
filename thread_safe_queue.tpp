#ifndef THREAD_SAFE_QUEUE_TPP
# define THREAD_SAFE_QUEUE_TPP

template<typename TType>
ThreadSafeQueue<TType>::ThreadSafeQueue() {}

template<typename TType>
ThreadSafeQueue<TType>::~ThreadSafeQueue() {}

template<typename TType>
void ThreadSafeQueue<TType>::push_back(const TType& newElement) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push_back(newElement);
}

template<typename TType>
void ThreadSafeQueue<TType>::push_front(const TType& newElement) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push_front(newElement);
}

template<typename TType>
TType ThreadSafeQueue<TType>::pop_back() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        throw std::runtime_error("Queue is empty");
    }
    TType element = queue_.back();
    queue_.pop_back();
    return element;
}

template<typename TType>
TType ThreadSafeQueue<TType>::pop_front() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        throw std::runtime_error("Queue is empty");
    }
    TType element = queue_.front();
    queue_.pop_front();
    return element;
}

template<typename TType>
size_t ThreadSafeQueue<TType>::size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}

template<typename TType>
bool ThreadSafeQueue<TType>::empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}

template<typename TType>
void ThreadSafeQueue<TType>::clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.clear();
}

#endif

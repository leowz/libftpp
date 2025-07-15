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
	ThreadSafeBlockingQueue();
	~ThreadSafeBlockingQueue();
    
	void    push_back(const T& item);
	void    push_front(T&& item);
	T   pop_back();
	T   pop_front();
    void stop();

private:
    ThreadSafeBlockingQueue(const ThreadSafeBlockingQueue&);
    ThreadSafeBlockingQueue& operator=(const ThreadSafeBlockingQueue&);

	std::deque<T> queue_;
	std::mutex mutex_;
	std::condition_variable condVar_;
    bool stopped_;
};

#include "thread_safe_blocking_queue.tpp"

#endif
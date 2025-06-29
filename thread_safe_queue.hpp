/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe_queue.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:47:34 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/29 13:13:40 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_SAFE_QUEUE_HPP
# define THREAD_SAFE_QUEUE_HPP

#include <deque>
#include <mutex>
#include <stdexcept>

template<typename TType>
class ThreadSafeQueue
{
public:
	ThreadSafeQueue() = default;
	~ThreadSafeQueue() = default;

	ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

	void	push_back(const TType& newElement);
	void	push_front(const TType& newElement);
	TType	pop_back();
	TType	pop_front();

	size_t	size() const;
	bool	empty() const;
	void	clear();

private:
	std::deque<TType>	queue_;

	// use mutable so in const method, can be locked
	mutable std::mutex mutex_;
};

# include "thread_safe_queue.tpp"

#endif

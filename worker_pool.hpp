/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_pool.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:37:31 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/30 16:37:41 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_POOL_HPP
# define WORKER_POOL_HPP

#include "thread_safe_blocking_queue.hpp"
#include <thread>
#include <vector>
#include <functional>
#include <atomic>

class WorkerPool
{
public:
	WorkerPool(size_t threadCount);
	~WorkerPool();

	void addJob(std::function<void()> jobToExecute);
    void stop();

    class IJobs
    {
    public:
        virtual void execute() = 0;
    };


private:
    // Prevent copying
    WorkerPool(const WorkerPool&);
    WorkerPool& operator=(const WorkerPool&);

    void workerLoop(); 
    ThreadSafeBlockingQueue<std::function<void()>> jobQueue_;
    std::vector<std::thread> workers_;
    std::atomic<bool> running_;
};

#endif

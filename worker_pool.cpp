/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_pool.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:20:51 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/30 23:20:52 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worker_pool.hpp"

WorkerPool::WorkerPool(size_t threadCount) : running_(true) {
    for (size_t i = 0; i < threadCount; ++i) {
        // the way to create thread for a class method, need to bind this
        workers_.emplace_back(&WorkerPool::workerLoop, this);
    }
}

WorkerPool::~WorkerPool() {
    stop();
}

void WorkerPool::addJob(std::function<void()> jobToExecute)
{
    jobQueue_.push_back(jobToExecute);
}

void WorkerPool::stop()
{
    if (running_.exchange(false)) {
        jobQueue_.stop(); // queue not blocking anymore
        for (auto& worker : workers_) {
            if (worker.joinable()) worker.join();
        }
    }
}

void WorkerPool::workerLoop()
{
    while (running_.load()) {
        try {
            auto job = jobQueue_.pop_front();
            job();
        } catch (const std::exception& e) {
            break;
        }
    }
}
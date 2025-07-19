/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persistent_worker.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:36:58 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/01 13:37:13 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "persistent_worker.hpp"

PersistentWorker::PersistentWorker():running_(false) {
    workerThread_ = std::thread(&PersistentWorker::runLoop, this);
}

PersistentWorker::~PersistentWorker() {
    if (running_.load()) {
        running_.store(false);
        if (workerThread_.joinable()) {
            workerThread_.join();
        }
    }
}

void    PersistentWorker::addTask(const std::string& name, const std::function<void()>&
			jobToExecute)
{
    std::lock_guard<std::mutex> lock(taskMutex_);
    taskMap_[name] = jobToExecute;
}

void    PersistentWorker::removeTask(const std::string& name)
{
    std::lock_guard<std::mutex> lock(taskMutex_);
    taskMap_.erase(name);
}

void    PersistentWorker::runLoop()
{
    running_.store(true);
    while (running_.load()) {
        std::unordered_map<std::string, std::function<void()>> localTasks;
        {
            // need to use local tasks because we are iterating over taskMap_
            // while potentially modifying it
            std::lock_guard<std::mutex> lock(taskMutex_);
            localTasks = taskMap_; // copy tasks
        }
        for (const auto& pair  : localTasks) {
            try {
                pair.second();
            } catch (const std::exception& e) {
                threadSafeCout << "PersistentWorker: " << pair.first << " caught exception: " << e.what() << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep to avoid busy waiting
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persistent_worker.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:23:02 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/01 13:33:37 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERSISTENT_WORKER_HPP
# define PERSISTENT_WORKER_HPP

#include "thread_safe_iostream.hpp"
#include <string>
#include <functional>
#include <map>
#include <unordered_map> 
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

class PersistentWorker
{
public:
	PersistentWorker();
	~PersistentWorker();

    // Add a task by name
    void	addTask(const std::string& name, const std::function<void()>&
			jobToExecute);
    // Remove a task by name
    void	removeTask(const std::string& name);

private:
	void	runLoop();	
    // Disable copy and move
    PersistentWorker(const PersistentWorker&) ;
    PersistentWorker& operator=(const PersistentWorker&);


	std::unordered_map<std::string, std::function<void()>> taskMap_;
    std::mutex taskMutex_;

    std::atomic<bool> running_;
    std::thread workerThread_;
};

#endif

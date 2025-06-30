/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:57:36 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/30 12:57:40 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.hpp"

Thread::Thread(const std::string& name, std::function<void()> functionToExecute)
    : name_(name), task_(functionToExecute), started_(false) {
}

Thread::~Thread() {
    stop();
}

void Thread::start() {
    if (started_.exchange(true)) {
        throw std::runtime_error("Thread '" + name() + "' already started");
    }
    thread_ = std::thread(&Thread::threadEntry, this);
}

void Thread::stop() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

void Thread::threadEntry(Thread* instance) {
        threadSafeCout.setPrefix("[" + instance->name() + "] ");
        instance->task_();
}

const std::string& Thread::name() const {
    return name_;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe_iostream.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:13:54 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/29 11:17:44 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_safe_iostream.hpp"

std::mutex ThreadSafeIOStream::outputMutex;
std::mutex ThreadSafeIOStream::inputMutex;
thread_local std::string ThreadSafeIOStream::threadPrefix = "";
thread_local ThreadSafeIOStream threadSafeCout;
thread_local ThreadSafeIOStream threadSafeCin;
thread_local bool ThreadSafeIOStream::isNewLine = true;

ThreadSafeIOStream::ThreadSafeIOStream() {};

void ThreadSafeIOStream::setPrefix(const std::string& prefix)
{
	threadPrefix = prefix;
}

ThreadSafeIOStream&
ThreadSafeIOStream::operator<<(std::ostream& (*manip)(std::ostream&))
{
    std::lock_guard<std::mutex> lock(outputMutex);
    manip(std::cout);
    isNewLine = true;
    return *this;
}

void ThreadSafeIOStream::printPrefixIfNewLine() {
    if (isNewLine && !threadPrefix.empty()) {
        std::cout << threadPrefix;
        isNewLine = false;
    }
}


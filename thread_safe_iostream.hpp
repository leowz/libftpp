/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe_iostream.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:20:30 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/29 11:18:38 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_SAFE_IOSTREAM_HPP
# define THREAD_SAFE_IOSTREAM_HPP

#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

class ThreadSafeIOStream
{
public:
	ThreadSafeIOStream();

	template<typename T>
	ThreadSafeIOStream&	operator<<(const T& value);

	// support for manipulators like std::endl which is function pointer
	ThreadSafeIOStream& operator<<(std::ostream& (*manip)(std::ostream&));

	template<typename T>
	ThreadSafeIOStream&	operator>>(T& value);


	void	setPrefix(const std::string& prefix);

	template<typename T>
	void	prompt(const std::string& question, T& dest);

private:
	static std::mutex	outputMutex;
	static std::mutex	inputMutex;

	thread_local static	std::string	threadPrefix;
	thread_local static bool isNewLine;

	void printPrefixIfNewLine();
};

extern thread_local ThreadSafeIOStream threadSafeCout;
extern thread_local ThreadSafeIOStream threadSafeCin;

# include "thread_safe_iostream.tpp"

#endif

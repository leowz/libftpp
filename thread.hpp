/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:42:18 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/29 17:13:52 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_HPP
# define THREAD_HPP


#include <thread>
#include <string>
#include <functional>
#include <atomic>

#include "thread_safe_iostream.hpp" 

class Thread
{
public:
	Thread(const std::string& name, std::function<void()> functionToExecute);
	~Thread();


	void	start();
	void	stop();

	const std::string&	name() const;

private:
	std::string	name_;
	std::function<void()>	task_;
	std::thread	thread_;
	std::atomic<bool>	started_;

	static void threadEntry(Thread* instance);
};

#endif

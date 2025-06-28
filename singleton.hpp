/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:40:47 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/28 21:32:30 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SINGLETON_HPP
# define SINGLETON_HPP

# include <stdexcept>

template<typename TType>
class Singleton
{

public: 
	static TType*	instance()
	{
		if (!instance_)
		{
			throw std::runtime_error("Instance not yet created");
		}
		else
		{
			return instance_;
		}
	}

	template<typename... TArgs>
	static void		instantiate(TArgs&&... p_args)
	{
		if (instance_)
		{
			throw std::runtime_error("Instance already created");
		}
		instance_ = new TType(std::forward<TArgs>(p_args)...);
	}

private:
	Singleton();
	~Singleton();

	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static TType*	instance_;
};

template<typename TType>
TType* Singleton<TType>::instance_ = nullptr;


#endif

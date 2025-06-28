/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:25:32 by zweng             #+#    #+#             */
/*   Updated: 2025/05/28 16:41:30 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POOL_HPP
# define POOL_HPP

#include <vector>
#include <stack>
#include <memory>
#include <cstddef>
#include <utility>
#include <stdexcept>

template<typename TType>
class Pool {
	public:
		class Object;

		Pool();
		~Pool();

		void resize(const std::size_t& numberOfObjectStored);

		template<typename... TArgs>
		Object acquire(TArgs&&... p_args);
		
		class Object {
			public:
				Object(Pool* pool, std::size_t index, TType* ptr);
				~Object();

				TType* operator->();
				TType& operator*();

				Object(Object&& other);
				Object& operator=(Object&& other);


			private:
				Pool<TType>* pool_;
				std::size_t	 index_;
				TType* ptr_;

				// disable copy constructor
				bool valid_;
				Object(const Object& other);
				Object& operator=(const Object& other);
		};

	private:
		std::vector<unsigned char*> storage_;
		std::stack<std::size_t> freeIndex_;
		std::vector<bool> active_;

		void destroyObjectAt(std::size_t index);
};

# include "pool.tpp"

#endif 

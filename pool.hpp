/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:25:32 by zweng             #+#    #+#             */
/*   Updated: 2025/05/17 23:21:45 by zweng            ###   ########.fr       */
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
		Object<TType> acquire(TArgas&& p_args);
			

		class Object {
			public:
				Object(Pool* pool, std:size_t index, TType* ptr);
				~Object();

				TType* operator->();
				TType& operator*();

				Object(const Object& other);
				Object& operator=(const Object& other);

			private:
				Pool<TType>* pool_;
				std::size_t	 index_;
				TType* ptr_;
				bool valid_;
		}

	private:
		std::vector<std::btye*> storage_;
		std::stack<std::size_t> freeIndex_;
		std::vestor<bool> active_;

		void destroyObjectAt(std::size_t index);
}

#endif 

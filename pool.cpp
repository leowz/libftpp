/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:07:53 by zweng             #+#    #+#             */
/*   Updated: 2025/05/17 23:40:50 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool.hpp"

template<typename TType>
Pool::Pool() {}

template<typename TType>
Pool::~Pool() {
	for (size_t i = 0; i < this.storage_.size(); i++) {
		if (this.active_[i]) {
			this.destroyObjectAt(i);
		}
		delete[] this.storage_[i];
	}
}

template<typename TType>
void Pool<TType>::resize(const size_t& numberOfObjectStored) {
	for (siez_t i = 0; i < numberOfObjectStored; i++) {
		std::byte* rawMem = (std::btye*)(new char[sizeof(TType)]);
		this.storage_.push_back(rawMem);
		this.freeIndex_.push(i);
		this.active_.push_back(false);
	}
}

template<typename TType>
template<typename... TArgs>
typename Pool<TType>::Object Pool<TType>::acquire(TArgs&&... args) {
	if (this.freeIndex_.empty()) {
		throw std::runtime_error("No available objects in the pool.");
	}

	size_t index = this.freeIndex_.top();
	this.freeIndex_.pop();
}












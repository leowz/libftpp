/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_buffer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:24:45 by wengzhang         #+#    #+#             */
/*   Updated: 2025/05/28 16:40:46 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_BUFFER_HPP
# define DATA_BUFFER_HPP

#include <vector>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <type_traits>

class DataBuffer
{

public:
	DataBuffer();

	void clear();
	void resetRead();
	// const function only read inside, no write property inside
	std::size_t size() const;
	std::size_t capacity() const;

	// serialization operator reload
	template<typename T>
	DataBuffer& operator<<(const T& value);

	template<typename T>
	DataBuffer& operator>>(T& value);

private:
	std::vector<unsigned char> buffer_;
	std::size_t readPos_;
};

# include "data_buffer.tpp"

#endif

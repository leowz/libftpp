/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_buffer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:45:38 by wengzhang         #+#    #+#             */
/*   Updated: 2025/05/28 16:54:26 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_buffer.hpp"

DataBuffer::DataBuffer()
    : readPos_(0) {}

void DataBuffer::clear() {
    buffer_.clear();
    readPos_ = 0;
}

void DataBuffer::resetRead() {
    readPos_ = 0;
}

std::size_t DataBuffer::size() const {
    return buffer_.size();
}

std::size_t DataBuffer::capacity() const {
    return buffer_.capacity();
}

DataBuffer& DataBuffer::operator<<(const std::string& data) {
    size_t len = data.size();
    *this << len;
    buffer_.insert(buffer_.end(), data.begin(), data.end());
    return *this;
}

DataBuffer& DataBuffer::operator>>(std::string& data) {
    size_t len;
    *this >> len;

    if (readPos_ + len > buffer_.size()) {
        throw std::out_of_range("Not enough data to read string");
    }

    data.assign(reinterpret_cast<const char*>(buffer_.data() + readPos_), len);
    readPos_ += len;
    return *this;
}

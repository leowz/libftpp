/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:00:29 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/05 13:00:30 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.hpp"

Message::Message() : type_(3), readPos_(0) {
}

Message::Message(int type) : type_(type), readPos_(0) {
}

void    Message::clear() {
    buffer_.clear();
    readPos_ = 0;
}

void    Message::resetRead() {
    readPos_ = 0;
}

void    Message::print() const {
    std::cout << "Print Message: Message Type: " << type_ << ", Buffer Size: " << buffer_.size() << std::endl;
    std::cout << "Buffer Content: ";
    for (const auto& byte : buffer_) {
        std::cout << static_cast<int>(byte) << "("<< static_cast<char>(byte) << ") ";
    }
    std::cout << std::endl;
}

void    Message::printStr() const {
    uint64_t len;
    *this >> len;
    const char* str = reinterpret_cast<const char*>(buffer_.data() + readPos_); 
    std::cout << "PrintStr Message: Message Type: " << type_ << ", Buffer Size: " << buffer_.size() << std::endl;
    std::cout << "Buffer Content: ";
    std::cout << std::string(str, len) << std::endl;
}

Message& Message::operator<<(const std::string& data) {
    uint64_t len = data.size();
    *this << len;
    buffer_.insert(buffer_.end(), data.begin(), data.end());
    return *this;
}

const Message& Message::operator>>(std::string& data) const {
    uint64_t len;
    *this >> len;

    if (readPos_ + len > buffer_.size()) {
        throw std::out_of_range("Not enough data to read string");
    }

    data.assign(reinterpret_cast<const char*>(buffer_.data() + readPos_), len);
    readPos_ += len;
    return *this;
}


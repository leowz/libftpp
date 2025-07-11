/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:09:16 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/01 23:09:16 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <stdint.h>
#include <iostream>

class Message {
public:
    // using for alias
    using Type = int;
    Message();
    Message(int type);
    ~Message() = default;

    Message& operator<<(const std::string& data);
    const Message& operator>>(std::string& data) const;

    template <typename T>
    Message& operator<<(const T& content);

    template <typename T>
    const Message& operator>>(T& content) const;


    Type type() const { return type_; }

    void    clear();
    void    resetRead();
    void    print() const;
    void    printStr() const;

    const std::vector<uint8_t>& buffer() const { return buffer_; }

private:
    Type                    type_;
    std::vector<uint8_t>    buffer_;
    mutable size_t          readPos_;
};

#include "message.tpp"

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:15:36 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/05 13:15:41 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "message.hpp"

#include <unistd.h>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

class Client
{
public:
    using Action = std::function<void(Message&)>;

    Client();
    ~Client();

    void    connect(const std::string& address, const size_t& port);
    void    disconnect();
    void    defineAction(const Message::Type& messageType, const Action& action);
    void    send(const Message& message);
    void    update();

private:
    int     socket_ = -1;
    std::unordered_map<Message::Type, Action> actions_;
    std::vector<Message>    messages_;
    // std::mutex                                  messagesMutex_;
};

#endif
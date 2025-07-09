/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:06:17 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/06 19:06:18 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "message.hpp"
#include <unordered_map>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>

class Server {
public:
    using Action = std::function<void(long long&, const Message&)>;

    Server();
    ~Server();

    void    start(const size_t& p_port);
    void    defineAction(const Message::Type& messageType, const Action& action);
    void    sendTo(const Message& message, long long clientId);
    void    sendToArray(const Message& message, std::vector<long long> clientIds);
    void    sendToAll(const Message& message);
    void    update();
    void    stop();
    void    removeClient(long long& clientId);

private:
    int                                         serverSocket_ = -1;
    std::atomic<long long>                      nextClientID_{1};
    std::unordered_map<long long, int>          clients_;
    std::unordered_map<Message::Type, Action>   actions_;
    std::vector<std::pair<long long, Message>>  incoming_;

    std::mutex                                  mutex_;
    std::vector<std::thread>                    threads_;
    std::atomic<bool>                           running_{false};

    void    acceptClients();
    void    handleClient(long long clientID, int clientSocket);
};



#endif
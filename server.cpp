/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:06:22 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/06 19:06:23 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server() {}

Server::~Server() {
    running_ = false;
    {
        std::lock_guard<std::mutex> lock(threadsMutex_);
        for (auto& t : threads_) {
            if (t.joinable()) t.join();
        }
    }
    if (serverSocket_ != -1) {
        ::close(serverSocket_);
    }
    for (auto& client : clients_) {
        ::close(client.second);
    }
}

void    Server::start(const size_t& port) {
    // std::cout << "Starting server on port " << port << std::endl;
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ < 0) {
        std::cout << "Failed to create server socket" << std::endl;
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    serverAddr.sin_port = htons(port);

    // bind address to server socket
    if (::bind(serverSocket_, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cout << "Failed to bind server socket" << std::endl;
        ::close(serverSocket_);
        return;
    }

    if (::listen(serverSocket_, SOMAXCONN) < 0) {
        std::cout << "Listen failed\n";
        return;
    }

    running_ = true;
    {
        std::lock_guard<std::mutex> lock(threadsMutex_);
        threads_.emplace_back(&Server::acceptClients, this);
    }
}

void Server::acceptClients() {
    int flags = fcntl(serverSocket_, F_GETFL, 0);
    fcntl(serverSocket_, F_SETFL, flags | O_NONBLOCK);
    while (running_) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(serverSocket_, &read_fds);
        int max_fd = serverSocket_;

        // Timeout: 1 second
        timeval timeout{};
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        // Wait for readiness to accept
        int activity = ::select(max_fd + 1, &read_fds, nullptr, nullptr, &timeout);
        if (activity < 0) {
            continue;
        }
        if (activity == 0) {
            continue;
        }
        if (FD_ISSET(serverSocket_, &read_fds)) {
            sockaddr_in clientAddr{};
            socklen_t clientSize = sizeof(clientAddr);
            int clientSocket = ::accept(serverSocket_, (sockaddr*)&clientAddr, &clientSize);
            if (clientSocket < 0) {
                continue;
            }
            long long clientID = nextClientID_++;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                clients_[clientID] = clientSocket;
            }
            {
                std::lock_guard<std::mutex> lock(threadsMutex_);
                threads_.emplace_back(&Server::handleClient, this, clientID, clientSocket);
            }
        }
    }
}

void Server::handleClient(long long clientID, int clientSocket) {
    while (running_) {
        uint64_t msgSize = 0;
        ssize_t bytes = recv(clientSocket, &msgSize, sizeof(msgSize), MSG_DONTWAIT);
        if (bytes < 0) {
            // In none blocking mode, recv() can return EAGAIN or EWOULDBLOCK if no data is available
            // so this should not be considered an error
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                continue;
            } else {
                //std::cerr << "recv() error from client " << clientID << ": " << strerror(errno) << std::endl;
                break;
            }
        } else if (bytes == 0) {
            // Client disconnected
            break;
        }

        Message::Type type;
        recv(clientSocket, &type, sizeof(type), 0);

        std::vector<uint8_t> data(msgSize - sizeof(type));
        recv(clientSocket, data.data(), data.size(), 0);

        Message msg(type);
        for (auto byte : data) {
            msg << byte;
        }
        std::lock_guard<std::mutex> lock(mutex_);
        incoming_.emplace_back(clientID, std::move(msg));
    }

    {
        std::lock_guard<std::mutex> lock(mutex_);
        clients_.erase(clientID);
        ::close(clientSocket);
    }
}

void Server::defineAction(const Message::Type& type, const Action& action) {
    actions_[type] = action;
}

void Server::sendTo(const Message& message, long long clientID) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = clients_.find(clientID);
    if (it == clients_.end()) {
        std::cout << "Client ID " << clientID << " not found." << std::endl;
        return;
    }

    const auto& buffer = message.buffer();
    uint64_t size = buffer.size() + sizeof(Message::Type);
    auto type = message.type();
    ::send(it->second, &size, sizeof(size), 0);
    ::send(it->second, &type, sizeof(Message::Type), 0);
    ::send(it->second, buffer.data(), buffer.size(), 0);
}

void Server::sendToArray(const Message& message, const std::vector<long long> clientIDs) {
    for (auto id : clientIDs) {
        sendTo(message, id);
    }
}

void Server::sendToAll(const Message& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& client : clients_) {
        sendTo(message, client.first);
    }
}

void Server::update() {
    std::vector<std::pair<long long, Message>> toProcess;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        // swap the incoming messages to process them, clear incoming_ for next round
        toProcess.swap(incoming_);
        // std::cout<< "Processing " << toProcess.size() << " incoming messages." << std::endl;
        incoming_.clear();
    }

    for (auto& process : toProcess) {
        auto it = actions_.find(process.second.type());
        if (it != actions_.end()) {
            it->second(process.first, process.second);
        }
    }
}



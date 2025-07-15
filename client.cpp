/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:15:46 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/05 13:15:46 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "client.hpp"

Client::Client() {}

Client::~Client() {
    disconnect();
}

void Client::connect(const std::string& address, const size_t& port) {
    // call socket from global scope not class scope
    // std::cout << "Connecting to " << address << ":" << port << std::endl;
    socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &serverAddr.sin_addr);

    if (::connect(socket_, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        ::close(socket_);
        socket_ = -1;
    }
}

void Client::disconnect() {
    if (socket_ >= 0) {
        ::close(socket_);
        socket_ = -1;
    }
}

void Client::defineAction(const Message::Type& messageType, const std::function<void(Message&)>& action) {
    actions_[messageType] = action;
}

void Client::send(const Message& message) {
    // debug
    // std::cout << "Sending message..." << std::endl;
    // if (message.type() == 4) {
    //     message.printStr();
    // } else {
    //     message.print();
    // }
    if (socket_ < 0) {
        std::cerr << "Socket is not connected" << std::endl;
        return;
    }

    const auto& buffer = message.buffer();
    uint64_t size = buffer.size() + sizeof(Message::Type);
    auto type = message.type();
    if (::send(socket_, &size, sizeof(size), 0) < 0) {
        std::cerr << "Failed to send message size" << std::endl;
    }
    if (::send(socket_, &type, sizeof(Message::Type), 0) < 0) {
        std::cerr << "Failed to send message type" << std::endl;
    }
    if (::send(socket_, buffer.data(), buffer.size(), 0) < 0) {
        std::cerr << "Failed to send message" << std::endl;
    }
    // std::cout << "Message sent: type = " << type << ", size = " << size << std::endl;
}

void Client::update() {
    // std::cout << "Updating client..." << std::endl;
    if (socket_ < 0) {
        std::cerr << "Socket is not connected" << std::endl;
        return;
    }

    uint64_t msgSize = 0;
    if (recv(socket_, &msgSize, sizeof(msgSize), MSG_DONTWAIT) <= 0) {
        std::cerr << "Socket: message size not received" << std::endl;
        return; // nothing to read
    }

    Message::Type type;
    if (recv(socket_, &type, sizeof(type), 0) <= 0) {
        std::cerr << "Socket: message type not received" << std::endl;
        return; // nothing to read
    }

    std::vector<uint8_t> data(msgSize - sizeof(type));
    if (recv(socket_, data.data(), data.size(), 0) <= 0) {
        std::cerr << "Socket: message type not received" << std::endl;
        return; // nothing to read
    }

    Message message(type); // Placeholder type, should be set based on protocol
    for (auto byte : data) {
        message << byte;
    }
    messages_.push_back(message);
    for (auto& msg : messages_) {
        auto it = actions_.find(msg.type());
        if (it != actions_.end()) {
            it->second(msg);
        }
    }
    messages_.clear();
}
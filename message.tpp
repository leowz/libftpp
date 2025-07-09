#ifndef MESSAGE_TPP
#define MESSAGE_TPP

template<typename T>
Message& Message::operator<<(const T& data) {
    size_t size = sizeof(T);
    buffer_.insert(buffer_.end(), reinterpret_cast<const uint8_t*>(&data), reinterpret_cast<const uint8_t*>(&data) + size);
    return *this;
}

template<typename T>
const Message& Message::operator>>(T& data) const {
    size_t size = sizeof(T);
    if (readPos_ + size > buffer_.size()) {
        throw std::out_of_range("Read position exceeds buffer size");
    }
    std::memcpy(&data, buffer_.data() + readPos_, size);
    readPos_ += size;
    return *this;
}

// template<>
// Message& Message::operator<<(const std::string& data) {
//     uint64_t len = data.size();
//     *this << len;
//     buffer_.insert(buffer_.end(), data.begin(), data.end());
//     return *this;
// }

// template<>
// Message& Message::operator>>(std::string& data) {
//     uint64_t len;
//     *this >> len;

//     if (m_readPos + len > buffer_.size()) {
//         throw std::out_of_range("Not enough data to read string");
//     }

//     data.assign(reinterpret_cast<const char*>(buffer_.data() + readPos_), len);
//     readPos_ += len;
//     return *this;
// }

#endif
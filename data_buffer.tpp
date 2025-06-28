#ifndef DATA_BUFFER_TPP
# define DATA_BUFFER_TPP

template<typename T>
DataBuffer& DataBuffer::operator<<(const T& value)
{
/*	static_assert(std::is_trivially_copyable<T>::value, "Only trivially \
			copyable types can be deserialised.\n"); */

	const unsigned char* raw = reinterpret_cast<const unsigned char*>(&value);
	buffer_.insert(buffer_.end(), raw, raw + sizeof(T));
	return *this;
}

template<typename T>
DataBuffer& DataBuffer::operator>>(T& value)
{
/*	static_assert(std::is_trivially_copyable<T>::value, "Only trivially \
			copyable types can be deserialised.\n"); */

	if (readPos_ + sizeof(T) > buffer_.size())
	{
		throw std::runtime_error("DataBuffer underflow during read.");
	}

	std::memcpy(&value, buffer_.data() + readPos_, sizeof(T));
	readPos_ += sizeof(T);	
	return *this;
}

#endif
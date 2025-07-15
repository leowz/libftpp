#ifndef IVECTOR2_TPP
# define IVECTOR2_TPP

template<typename TType>
IVector2<TType>::IVector2(TType x, TType y) : x(x), y(y) {}

template<typename TType>
IVector2<TType>& IVector2<TType>::operator=(const IVector2<TType>& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template<typename TType>
IVector2<TType> IVector2<TType>::operator+(const IVector2<TType>& other) const {
    return IVector2(x + other.x, y + other.y);
}

template<typename TType>
IVector2<TType> IVector2<TType>::operator-(const IVector2<TType>& other) const {
    return IVector2(x - other.x, y - other.y);
}

template<typename TType>
IVector2<TType> IVector2<TType>::operator*(const TType& scalar) const {
    return IVector2(x * scalar, y * scalar);
}

template<typename TType>
IVector2<TType> IVector2<TType>::operator*(const IVector2<TType>& other) const {
    return IVector2(x * other.x, y * other.y);
}

template<typename TType>
IVector2<TType> IVector2<TType>::operator/(const TType& scalar) const {
    if (scalar == 0) {
        throw std::runtime_error("Division by zero in IVector2.");
    }
    return IVector2(x / scalar, y / scalar);
}

template<typename TType>
IVector2<TType> IVector2<TType>::operator/(const IVector2<TType>& other) const {
    if (other.x == 0 || other.y == 0) {
        throw std::runtime_error("Division by zero in IVector2.");
    }
    return IVector2(x / other.x, y / other.y);
}

template<typename TType>
IVector2<TType> IVector2<TType>::operator-() const {
    return IVector2(-x, -y);
}

template<typename TType>
bool IVector2<TType>::operator==(const IVector2<TType>& other) const {
    return (x == other.x && y == other.y);
}

template<typename TType>
bool IVector2<TType>::operator!=(const IVector2<TType>& other) const {
    return !(*this == other);
}

template<typename TType>
float IVector2<TType>::length() const {
    return std::sqrt(static_cast<float>(x * x + y * y));
}

template<typename TType>
float IVector2<TType>::lengthSquared() const {
    return static_cast<float>(x * x + y * y);
}

template<typename TType>
IVector2<float> IVector2<TType>::normalize() const {
    float len = length();
    if (len == 0) {
        throw std::runtime_error("Cannot normalize a zero-length vector.");
    }
    return IVector2<float>(x / len, y / len);
}

template<typename TType>
float IVector2<TType>::dot() const {
    return x * x + y * y;
}

template<typename TType>
float IVector2<TType>::dot(IVector2<TType> other) const {
    return x * other.x + y * other.y;
}

template<typename TType>
IVector2<TType> IVector2<TType>::cross() const {
    return IVector2(-y, x);
}

template<typename TType>
IVector2<TType> IVector2<TType>::cross(IVector2<TType> other) const {
    return IVector2(-y * other.x + x * other.y, x * other.y - y * other.x);
}

#endif

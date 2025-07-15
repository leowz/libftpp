#ifndef IVECTOR3_TPP
# define IVECTOR3_TPP

template<typename TType>
IVector3<TType>::IVector3(TType x, TType y, TType z) : x(x), y(y), z(z) {}

template<typename TType>
IVector3<TType>& IVector3<TType>::operator=(const IVector3<TType>& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

template<typename TType>
IVector3<TType> IVector3<TType>::operator+(const IVector3<TType>& other) const {
    return IVector3(x + other.x, y + other.y, z + other.z);
}

template<typename TType>
IVector3<TType> IVector3<TType>::operator-(const IVector3<TType>& other) const {
    return IVector3(x - other.x, y - other.y, z - other.z);
}

template<typename TType>
IVector3<TType> IVector3<TType>::operator*(const TType& scalar) const {
    return IVector3(x * scalar, y * scalar, z * scalar);
}

template<typename TType>
IVector3<TType> IVector3<TType>::operator*(const IVector3<TType>& other) const {
    return IVector3(x * other.x, y * other.y, z * other.z);
}

template<typename TType>
IVector3<TType> IVector3<TType>::operator/(const TType& scalar) const {
    if (scalar == 0) {
        throw std::runtime_error("Division by zero in ivector3.");
    }
    return IVector3(x / scalar, y / scalar, z / scalar);
}

template<typename TType>
IVector3<TType> IVector3<TType>::operator/(const IVector3<TType>& other) const {
    if (other.x == 0 || other.y == 0 || other.z == 0) {
        throw std::runtime_error("Division by zero in ivector3.");
    }
    return IVector3(x / other.x, y / other.y, z / other.z);
}

template<typename TType>
IVector3<TType> IVector3<TType>::operator-() const {
    return IVector3(-x, -y, -z);
}

template<typename TType>
bool IVector3<TType>::operator==(const IVector3<TType>& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

template<typename TType>
bool IVector3<TType>::operator!=(const IVector3<TType>& other) const {
    return !(*this == other);
}

template<typename TType>
float IVector3<TType>::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

template<typename TType>
IVector3<float> IVector3<TType>::normalize() const {
    float len = length();
    if (len == 0) {
        throw std::runtime_error("Cannot normalize a zero-length vector.");
    }
    return IVector3<float>(x / len, y / len, z / len);
}

template<typename TType>
float IVector3<TType>::dot(const IVector3<TType>& other) const {
    return x * other.x + y * other.y + z * other.z;
}

template<typename TType>
IVector3<TType> IVector3<TType>::cross(const IVector3<TType>& other) const {
    return IVector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

#endif
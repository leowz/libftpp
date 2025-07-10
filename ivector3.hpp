/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ivector3.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:22:57 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/10 12:22:58 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IVECTOR3_HPP
#define IVECTOR3_HPP

template<typename TType>
struct IVector3
{
    TType x;
    TType y;
    TType z;

    IVector3(TType x, TType y, TType z) : x(x), y(y), z(z) {}

    IVector3<TType>& operator=(const IVector3<TType>& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    IVector3 operator+(const IVector3& other) const {
        return IVector3(x + other.x, y + other.y, z + other.z);
    }

    IVector3 operator-(const IVector3& other) const {
        return IVector3(x - other.x, y - other.y, z - other.z);
    }

    IVector3 operator*(const TType& scalar) const {
        return IVector3(x * scalar, y * scalar, z * scalar);
    }

    IVector3 operator*(const IVector3& other) const {
        return IVector3(x * other.x, y * other.y, z * other.z);
    }

    IVector3 operator/(const TType& scalar) const {
        if (scalar == 0) {
            throw std::runtime_error("Division by zero in ivector3.");
        }
        return IVector3(x / scalar, y / scalar, z / scalar);
    }

    IVector3 operator/(const IVector3& other) const {
        if (other.x == 0 || other.y == 0 || other.z == 0) {
            throw std::runtime_error("Division by zero in ivector3.");
        }
        return IVector3(x / other.x, y / other.y, z / other.z);
    }

    IVector3 operator-() const {
        return IVector3(-x, -y, -z);
    }
    
    bool operator==(const IVector3& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    bool operator!=(const IVector3& other) const {
        return !(*this == other);
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    IVector3<float> normalize() const {
        float len = length();
        if (len == 0) {
            throw std::runtime_error("Cannot normalize a zero-length vector.");
        }
        return IVector3<float>(x / len, y / len, z / len);
    }

    float dot(const IVector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    IVector3 cross(const IVector3& other) const {
        return IVector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
};

# endif

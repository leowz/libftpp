/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ivector2.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:46:17 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/09 17:46:18 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IVECTOR2_HPP
#define IVECTOR2_HPP

#include <iostream> 

template<typename TType>
struct IVector2
{      
    TType x;
    TType y;

    IVector2(TType x, TType y) : x(x), y(y) {}

    IVector2<TType>& operator=(const IVector2<TType>& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    IVector2 operator+(const IVector2& other) const {
        return IVector2(x + other.x, y + other.y);
    }

    IVector2 operator-(const IVector2& other) const {
        return IVector2(x - other.x, y - other.y);
    }

    IVector2 operator*(const TType& scalar) const {
        return IVector2(x * scalar, y * scalar);
    }

    IVector2 operator*(const IVector2& other) const {
        return IVector2(x * other.x, y * other.y);
    }

    IVector2 operator/(const TType& scalar) const {
        if (scalar == 0) {
            throw std::runtime_error("Division by zero in IVector2.");
        }
        return IVector2(x / scalar, y / scalar);
    }

    IVector2 operator/(const IVector2& other) const {
        if (other.x == 0 || other.y == 0) {
            throw std::runtime_error("Division by zero in IVector2.");
        }
        return IVector2(x / other.x, y / other.y);
    }

    IVector2  operator-() const {
        return IVector2(-x, -y);
    }

    bool operator==(const IVector2& other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const IVector2& other) const {
        return !(*this == other);
    }

    float length() const {
        return std::sqrt(static_cast<float>(x * x + y * y));
    }

    float lengthSquared() const {
        return static_cast<float>(x * x + y * y);
    }

    IVector2<float> normalize() const {
        float len = length();
        if (len == 0) {
            throw std::runtime_error("Cannot normalize a zero-length vector.");
        }
        return IVector2<float>(x / len, y / len);
    }

    float dot() const {
        return x * x + y * y;
    }

    float dot(IVector2<TType> other) const {
        return x * other.x + y * other.y;
    }

    IVector2<TType> cross() const {
        return IVector2(-y, x);
    }

    IVector2<TType> cross(IVector2<TType> other) const {
        return IVector2(-y * other.x + x * other.y, x * other.y - y * other.x);
    }
};

#endif

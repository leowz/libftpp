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

#include <iostream>
#include <cmath>
#include <algorithm>

template<typename TType>
struct IVector3
{
    TType x;
    TType y;
    TType z;

    IVector3(TType x, TType y, TType z); 
    IVector3<TType>& operator=(const IVector3<TType>& other);
    IVector3    operator+(const IVector3& other) const;
    IVector3    operator-(const IVector3& other) const;
    IVector3    operator*(const TType& scalar) const;
    IVector3    operator*(const IVector3& other) const;
    IVector3    operator/(const TType& scalar) const;
    IVector3    operator/(const IVector3& other) const;
    IVector3    operator-() const;
    bool        operator==(const IVector3& other) const;
    bool        operator!=(const IVector3& other) const;
    float       length() const;
    IVector3<float> normalize() const;
    float       dot(const IVector3& other) const;
    IVector3    cross(const IVector3& other) const;
};

#include "ivector3.tpp"

# endif

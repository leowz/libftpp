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

    IVector2(TType x, TType y); 

    IVector2<TType>&    operator=(const IVector2<TType>& other); 
    IVector2<TType>     operator+(const IVector2<TType>& other) const;
    IVector2<TType>     operator-(const IVector2<TType>& other) const;
    IVector2<TType>     operator*(const TType& scalar) const;
    IVector2<TType>     operator*(const IVector2<TType>& other) const;
    IVector2<TType>     operator/(const TType& scalar) const;
    IVector2<TType>     operator/(const IVector2<TType>& other) const;
    IVector2<TType>     operator-() const;
    bool operator==(const IVector2<TType>& other) const;
    bool operator!=(const IVector2<TType>& other) const;
    float length() const;
    float lengthSquared() const;
    IVector2<float> normalize() const;
    float dot() const;
    float dot(IVector2<TType> other) const;
    IVector2<TType> cross() const;
    IVector2<TType> cross(IVector2<TType> other) const;
};

#include "ivector2.tpp"

#endif

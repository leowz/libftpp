/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_2D_coordinate_generator.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:47:07 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/10 12:47:08 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random_2D_coordinate_generator.hpp"

long long Random2DCoordinateGenerator::operator()(long long x, long long y) const {
    long long hash = seed_;

    hash ^= x + 0x9e3779b97f4a7c15;
    hash = (hash << 13) ^ (hash >> 7) ^ y;
    hash ^= (hash << 17) + (x << 3) + (y << 5);

    // Optional: scramble the bits a bit more
    hash ^= (hash >> 33);
    hash *= 0xff51afd7ed558ccdLL;
    hash ^= (hash >> 33);
    hash *= 0xc4ceb9fe1a85ec53LL;
    hash ^= (hash >> 33);

    return hash;
}

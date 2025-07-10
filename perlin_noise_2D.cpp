/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise_2D.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:47:49 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/10 12:47:50 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin_noise_2D.hpp"
#include <cmath>

PerlinNoise2D::PerlinNoise2D(unsigned int seed) : seed_(seed) {}

float   PerlinNoise2D::sample(float x, float y) const
{
    // Simple Perlin noise implementation
    int xi = static_cast<int>(std::floor(x)) & 255;
    int yi = static_cast<int>(std::floor(y)) & 255;

    float xf = x - std::floor(x);
    float yf = y - std::floor(y);

    // Fade function
    auto fade = [](float t) { return t * t * t * (t * (t * 6 - 15) + 10); };
    xf = fade(xf);
    yf = fade(yf);

    // Hashing function
    auto hash = [this](int x, int y) {
        return (x + y * 57 + seed_) % 256;
    };

    // Gradient vectors
    float gradX1 = hash(xi, yi);
    float gradY1 = hash(xi + 1, yi);
    float gradX2 = hash(xi, yi + 1);
    float gradY2 = hash(xi + 1, yi + 1);

    // Interpolation
    float n1 = gradX1 * xf + gradY1 * yf;
    float n2 = gradX2 * (xf - 1) + gradY2 * yf;
    
    return (n1 * (1 - xf) + n2 * xf) * (1 - yf) + (n2 * yf);

}
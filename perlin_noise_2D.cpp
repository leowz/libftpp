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

PerlinNoise2D::PerlinNoise2D(unsigned int seed) {
    permutation.resize(256);
    for (int i = 0; i < 256; ++i) permutation[i] = i;
    std::srand(seed);
    std::random_shuffle(permutation.begin(), permutation.end());
    permutation.insert(permutation.end(), permutation.begin(), permutation.end());
}

double PerlinNoise2D::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10); // 6t^5 - 15t^4 + 10t^3
}

double PerlinNoise2D::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double PerlinNoise2D::grad(int hash, double x, double y) {
    int h = hash & 7; // Take first 3 bits
    double u = h < 4 ? x : y;
    double v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
}

float   PerlinNoise2D::sample(float x, float y) const
{
    int X = (int)std::floor(x) & 255;
    int Y = (int)std::floor(y) & 255;

    x -= std::floor(x);
    y -= std::floor(y);

    double u = fade(x);
    double v = fade(y);

    int A = permutation[X] + Y;
    int B = permutation[X + 1] + Y;

    double result = lerp(v,
        lerp(u, grad(permutation[A], x, y), grad(permutation[B], x - 1, y)),
        lerp(u, grad(permutation[A + 1], x, y - 1), grad(permutation[B + 1], x - 1, y - 1))
    );
    return result; 
}
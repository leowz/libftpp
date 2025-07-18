/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise_2D.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:47:37 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/10 12:47:38 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_NOISE_2D_HPP
#define PERLIN_NOISE_2D_HPP

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

class PerlinNoise2D {
public:
    PerlinNoise2D(unsigned int seed = 0);
    float sample(float x, float y) const;

private:
    std::vector<int> permutation;

    static double fade(double t);
    static double lerp(double t, double a, double b);
    static double grad(int hash, double x, double y); 
};

#endif


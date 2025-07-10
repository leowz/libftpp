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

class PerlinNoise2D {

public:
    PerlinNoise2D(unsigned int seed = 0);
    float sample(float x, float y) const;

private:
    unsigned int    seed_;
};

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_2D_coordinate_generator.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:46:52 by wengzhang         #+#    #+#             */
/*   Updated: 2025/07/10 12:46:53 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_2D_COORDINATE_GENERATOR_HPP
# define RANDOM_2D_COORDINATE_GENERATOR_HPP

class Random2DCoordinateGenerator
{
private:
    long long seed_;

public:
    Random2DCoordinateGenerator(long long seed = 0) : seed_(seed) {}
    long long   seed() const { return seed_; }
    long long   operator()(long long x, long long y) const;
};

#endif

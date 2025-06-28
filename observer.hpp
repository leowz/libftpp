/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:57:21 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/28 20:34:58 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBSERVER_HPP
# define OBSERVER_HPP

# include <unordered_map>
# include <vector>
# include <functional>
# include <iostream>

template<typename TEvent>
class Observer
{

public:
	void subscribe(const TEvent& event, const std::function<void()>& lambda);
	void notify(const TEvent& event);
private:
	std::unordered_map<TEvent, std::vector<std::function<void()>>> subscriptions_;
};

# include "observer.tpp"

#endif

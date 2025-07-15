/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:39:31 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/28 22:41:32 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_MACHINE_HPP
# define STATE_MACHINE_HPP

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <stdexcept>

template<typename TState>
class StateMachine
{
public:
	void	addState(const TState& state);
	void	addTransition(const TState& startState,
				const TState& finalState,
				const std::function<void()>& lambda);
	void	addAction(const TState& state,
				const std::function<void()>& lambda);
	void	transitionTo(const TState& state);
	void	update();

private:
	TState	currentState_;

	template<typename T>
	struct PairHash
	{
		std::size_t operator()(const std::pair<T,T>& p) const;
	};
	std::unordered_set<TState>	allowedStates_;
	std::unordered_map<TState, std::function<void()>>	actions_;
	std::unordered_map<std::pair<TState, TState>,
		std::function<void()>, PairHash<TState>>	transitions_;
};

# include "state_machine.tpp"

#endif

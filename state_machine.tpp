#ifndef STATE_MACHINE_TPP
# define STATE_MACHINE_TPP

template<typename TState>
void StateMachine<TState>::addState(const TState& state)
{
    if (allowedStates_.size() <= 0)
    {
        currentState_ = state;
    }
	allowedStates_.insert(state);
}

template<typename TState>
void StateMachine<TState>::addTransition(const TState& startState, const TState& finalState, const std::function<void()>& lambda)
{
    transitions_[std::make_pair(startState, finalState)] = lambda;
}

template<typename TState>
void StateMachine<TState>::addAction(const TState& state, const std::function<void()>& lambda)
{
    actions_[state] = lambda;
}

template<typename TState>
void StateMachine<TState>::transitionTo(const TState& state)
{
    if (allowedStates_.find(state) == allowedStates_.end())
    {
        throw std::invalid_argument("Invalid transition: state not allowed.");
    }
    if (transitions_.find(std::make_pair(currentState_, state)) != transitions_.end())
    {
        transitions_[std::make_pair(currentState_, state)]();
    }
    else
    {
        throw std::invalid_argument("Handle state not found");
    }
    currentState_ = state;
}

template<typename TState>
void StateMachine<TState>::update()
{
    if (actions_.find(currentState_) != actions_.end())
    {
        actions_[currentState_]();
    }
}

template<typename TState>
template<typename T>
std::size_t StateMachine<TState>::PairHash<T>::operator()(const std::pair<T,T>& p) const
{
	// calculate first has ^ second hash
	return std::hash<T>()(p.first) ^ std::hash<T>()(p.second);	
}

#endif

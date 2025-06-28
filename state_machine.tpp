#ifndef STATE_MACHINE_TPP
# define STATE_MACHINE_TPP

template<typename TState>
void StateMachine<TState>::addState(const TState& state)
{
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
        throw std::runtime_error("Invalid transition: state not allowed.");
    }
    if (transitions_.find(std::make_pair(currentState_, state)) != transitions_.end())
    {
        transitions_[std::make_pair(currentState_, state)]();
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

#endif

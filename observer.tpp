#ifndef OBSERVER_TPP
# define OBSERVER_TPP

template<typename TEvent>
void Observer<TEvent>::subscribe(const TEvent& event, const std::function<void()>& lambda)
{
	subscriptions_[event].push_back(lambda);
}

template<typename TEvent>
void Observer<TEvent>::notify(const TEvent& event)
{
    auto it = subscriptions_.find(event);
    if (it == subscriptions_.end()) {
        std::cout << "None, as there are no subscribers" << std::endl;
        return;
    }
	for (const auto& lambda : it->second)
		lambda();
}

#endif

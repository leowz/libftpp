#ifndef SINGLETON_TPP
#define SINGLETON_TPP

template<typename TType>
TType* Singleton<TType>::instance_ = nullptr;

template<typename TType>
TType* Singleton<TType>::instance()
{
	if (!instance_)
	{
		throw std::runtime_error("Instance not yet created");
	}
	else
	{
		return instance_;
	}
}

template<typename TType>
template<typename... TArgs>
void Singleton<TType>::instantiate(TArgs&&... p_args)
{
	if (instance_)
	{
		throw std::runtime_error("Instance already created");
	}
	instance_ = new TType(std::forward<TArgs>(p_args)...);
}

template<typename TType>
void Singleton<TType>::destory()
{
	if (instance_)
	{
		delete instance_;
	}
}


#endif
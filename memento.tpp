#ifndef MEMENTO_TPP
# define MEMENTO_TPP

template<typename T>
Memento::Snapshot&	Memento::Snapshot::operator<<(const T& value)
{
	buffer() << value;
	return *this;
}

template<typename T>
Memento::Snapshot&	Memento::Snapshot::operator>>(T& value)
{
	buffer() >> value;
	return *this;
}

#endif
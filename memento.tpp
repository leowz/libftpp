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

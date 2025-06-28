/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memento.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:22:49 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/27 22:48:01 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMENTO_HPP
# define MEMENTO_HPP

# include "data_buffer.hpp"

class Memento
{
public: 
	class Snapshot
	{
	public: 
		Snapshot();

		template<typename T>
		Snapshot& operator<<(const T& value);
		template<typename T>
		Snapshot& operator>>(T& value);

		//buffer getter method
		DataBuffer&	buffer();
		//const DataBuffer& buffer() const;

	private:
		DataBuffer	buffer_;	
	};

	Snapshot	save() const; // make it callable on const object
	void		load(const Snapshot& state);

protected:
	// pure abstract method that needs an implementation in children
	virtual void _saveToSnapshot(Snapshot& snapshot) const = 0;
	virtual void _loadFromSnapshot(Snapshot& snapshot) = 0;
};

# include "memento.tpp"


#endif

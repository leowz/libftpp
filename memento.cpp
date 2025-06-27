/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memento.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wengzhang <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:26:09 by wengzhang         #+#    #+#             */
/*   Updated: 2025/06/27 22:57:38 by wengzhang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memento.hpp"

Memento::Snapshot::Snapshot(): buffer_() {}

DataBuffer&	Memento::Snapshot::buffer()
{
	return buffer_;
}

Memento::Snapshot	Memento::save() const 
{
	Memento::Snapshot	snapshot;
	_saveToSnapshot(snapshot);
	return snapshot;
}

void	Memento::load(const Memento::Snapshot& state) 
{
	_loadFromSnapshot(const_cast<Memento::Snapshot&>(state));
}



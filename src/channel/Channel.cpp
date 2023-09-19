/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/19 12:55:48 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Channel.hpp"

Channel::Channel(void) { return ; }

Channel::Channel(std::string& name, std::string& key)
	: _name(name), _userCount(0), _key(key), _topic("")
{
	this->creationTime = getCurrentTime();
	_initChannelModes();
	_initModeFunctions();
}

Channel::Channel(const Channel& other)
{
	*this = other;
}

Channel::~Channel(void) {}

Channel& Channel::operator=(const Channel& other) 
{ 
	if (this != &other)
	{
		this->_name = other._name;
		this->_topic = other._topic;
		this->_key = other._key;
		this->_limit = other._limit;
		this->creationTime = other.creationTime;
		copyVector(this->_operators, other._operators);
		copyVector(this->_canTalk, other._canTalk);
		copyVector(this->_onlineUsers, other._onlineUsers);
		copyVector(this->_bannedUsers, other._bannedUsers);
		copyMap(this->modes, other.modes);
		copyMap(this->modesWithParams, other.modesWithParams);
		copyMap(this->modesWithoutParams, other.modesWithoutParams);
	}
	return *this;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 18:18:35 by guilmira         ###   ########.fr       */
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
		size_t pos = 0;
		while (pos < other._operators.size())
		{
			this->_operators.push_back(other._operators[pos]);
			pos++;
		}
		pos = 0;
		while (pos < other._canTalk.size())
		{
			this->_canTalk.push_back(other._canTalk[pos]);
			pos++;
		}
		pos = 0;
		while (pos < other._onlineUsers.size())
		{
			this->_onlineUsers.push_back(other._onlineUsers[pos]);
			pos++;
		}
		pos = 0;
		while (pos < other._bannedUsers.size())
		{
			this->_bannedUsers.push_back(other._bannedUsers[pos]);
			pos++;
		}
		std::map<char, bool>::const_iterator itModes = other.modes.begin();
		while (itModes != other.modes.end())
		{
			this->modes[itModes->first] = itModes->second;
			itModes++;
		}
		std::map<char, modeWithParamsFunctions>::const_iterator itModesParams = other.modesWithParams.begin();
		while (itModesParams != other.modesWithParams.end())
		{
			this->modesWithParams[itModesParams->first] = itModesParams->second;
			itModesParams++;
		}
		std::map<char, modeFunctions>::const_iterator itModesWithout = other.modesWithoutParams.begin();
		while (itModesWithout != other.modesWithoutParams.end())
		{
			this->modesWithoutParams[itModesWithout->first] = itModesWithout->second;
			itModesWithout++;
		}
	}
	return *this;
}
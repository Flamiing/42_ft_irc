/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 15:53:45 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Channel.hpp"

Channel::Channel(void) {}

Channel::Channel(std::string& name) : _name(name), _key(""), _topic("")
{
	this->creationTime = getCurrentTime();
	
	this->modes[MODE_CHANNEL_OPERATOR] = false;
	this->modes[MODE_CHANNEL_PRIVATE] = false;
	this->modes[MODE_CHANNEL_SECRET] = false;
	this->modes[MODE_CHANNEL_INVITE_ONLY] = false;
	this->modes[MODE_CHANNEL_TOPIC_OPER_ONLY] = false;
	this->modes[MODE_CHANNEL_NO_MSG_FROM_OUTSIDE] = false;
	this->modes[MODE_CHANNEL_MODERATED] = false;
	this->modes[MODE_CHANNEL_USER_LIMIT] = false;
	this->modes[MODE_CHANNEL_BANNED] = false;
	this->modes[MODE_CHANNEL_SPEAK_ABILITY] = false;
	this->modes[MODE_CHANNEL_KEY] = false;

	this->modesWithParams[MODE_CHANNEL_OPERATOR] = &Channel::setO;
	this->modesWithParams[MODE_CHANNEL_KEY] = &Channel::setK;
	this->modesWithParams[MODE_CHANNEL_USER_LIMIT] = &Channel::setL;
	this->modesWithParams[MODE_CHANNEL_BANNED] = &Channel::setB;
	this->modesWithParams[MODE_CHANNEL_SPEAK_ABILITY] = &Channel::setV;
}

Channel::Channel(const Channel& other) { *this = other; }

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


std::string Channel::getName() const { return this->_name; }
size_t Channel::getUserCount() const { return this->_onlineUsers.size(); }
std::string Channel::getTopic() const { return this->_topic; }
std::string Channel::getKey() const { return this->_key; }
size_t Channel::getLimit() const { return this->_limit; }
//std::vector<Client> getBannedUsers(void) const { return this->_bannedUsers; }

std::string Channel::getOnlineUsersList()
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();
	std::string listOfUsers;

	while (it != this->_onlineUsers.end())
	{
		if (_checkOperator(it->getNickname()))
			listOfUsers += "@" + it->getNickname();
		else
			listOfUsers += it->getNickname();
		if ((it + 1) != this->_onlineUsers.end())
			listOfUsers += " ";
		it++;
	}
	return listOfUsers;
}

bool Channel::clientInChannel(std::string nickname)
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();

	while (it != this->_onlineUsers.end())
	{
		if (toUpperCase((*it).getNickname()) == toUpperCase(nickname))
			return true;
		it++;
	}
	return false;
}

void Channel::messageOnlineUsers(const std::string sender, const std::string& reply)
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();
	
	while (it != this->_onlineUsers.end())
	{
		if (toUpperCase(it->getNickname()) != toUpperCase(sender))
			send(it->getSocket(), reply.c_str(), reply.size(), 0);
		it++;
	}
}
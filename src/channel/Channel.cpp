/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 00:23:24 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Channel.hpp"

Channel::Channel(void) {}

Channel::Channel(std::string& name) : _name(name), _key(""), _topic("") {}

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
		size_t pos = 0;
		while (pos < other._onlineUsers.size())
		{
			this->_onlineUsers.push_back(other._onlineUsers[pos]);
			pos++;
		}
	}
	return *this;
}


std::string Channel::getName() const { return this->_name; }
size_t Channel::getUserCount() const { return this->_onlineUsers.size(); }
std::string Channel::getTopic() const { return this->_topic; }
std::string Channel::getKey() const { return this->_key; }
//std::vector<Client> getBannedUsers(void) const { return this->_bannedUsers; }

std::string Channel::getOnlineUsersList() const
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();
	std::string listOfUsers;

	while (it != this->_onlineUsers.end())
	{
		listOfUsers += it->getNickname();
		if ((it + 1) != this->_onlineUsers.end())
			listOfUsers += " ";
		it++;
	}
	return listOfUsers;
}

bool Channel::userIsBanned(std::string& nickname)
{
	std::vector<Client>::const_iterator it = this->_bannedUsers.begin();

	while (it != this->_bannedUsers.end())
	{
		if ((*it).getNickname() == nickname)
			return true;
		it++;
	}
	return false;
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
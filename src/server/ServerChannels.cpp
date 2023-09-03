/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:13:49 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/03 16:14:06 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::addChannel(std::string channelName)
{
	Channel newChannel(channelName);
	
	this->_channels.push_back(newChannel);
}

void Server::connectToChannel(std::string& channel, Client& client, std::string key)
{
	std::vector<Channel>::iterator it = this->_channels.begin();

	while (it != this->_channels.end())
	{
		if (it->getName() == channel)
		{
			it->joinChannel(client, key);
			return ;
		}
		it++;
	}
}

void Server::disconnectClientFromChannels(std::string client, std::string& reply)
{
	std::vector<Channel>::iterator it = this->_channels.begin();

	while (it != this->_channels.end())
	{
		if (it->clientInChannel(client))
			it->disconnectFromChannel(client, reply);
		it++;
	}
}

void Server::disconnectFromChannel(std::string& clientName, std::string& channelName, std::string& reply)
{
	std::vector<Channel>::iterator it = this->_channels.begin();

	while (it != this->_channels.end())
	{
		if (it->getName() == channelName && it->clientInChannel(clientName))
		{
			it->removeFromChannel(clientName, reply);
			break ;	
		}
		it++;
	}
	_removeChannelFromClient(clientName, channelName);
}

void Server::_removeChannelFromClient(std::string& clientName, std::string& channelName)
{
	std::map<int, Client>::iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (it->second.getNickname() == clientName)
		{
			it->second.removeChannel(channelName);
			break ;
		}
		it++;
	}
}

/* bool Server::isBanned(std::string& nickname, std::string& channel)
{
	std::vector<Channel>::iterator it = this->_channels.begin();

	while (it != this->_channels.end())
	{
		if ((*it).getName() == channel)
			if ((*it).userIsBanned(nickname))
				return true;
		it++;
	}
	return false;
} */
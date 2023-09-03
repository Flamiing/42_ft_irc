/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannelDisconnection.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:49:30 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/03 17:50:08 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::disconnectClientFromChannels(std::string client, std::string& reply)
{
	std::vector<Channel>::iterator it = this->_channels.begin();

	while (it != this->_channels.end())
	{
		if (it->clientInChannel(client))
		{
			it->disconnectFromChannel(client, reply);
			if (it->getUserCount() == 0)
			{
				this->_channels.erase(it);
				it--;
			}
		}
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
			if (it->getUserCount() == 0)
				this->_channels.erase(it);
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
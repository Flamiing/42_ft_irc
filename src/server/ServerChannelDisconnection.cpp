/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannelDisconnection.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:49:30 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/19 13:42:09 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::disconnectClientFromChannels(std::string client, std::string& reply)
{
	std::vector<Channel>::iterator it = this->channels.begin();

	while (it != this->channels.end())
	{
		if (it->clientInChannel(client))
		{
			it->disconnectFromChannel(client, reply);
			if (it->getUserCount() == 0)
			{
				std::cout << SERVER << BOLD_YELLOW << CHANNEL_DELETED((*it).getName()) << RESET;
				this->channels.erase(it);
				it--;
			}
		}
		it++;
	}
}

void Server::partFromChannel(Client& client, std::string& channelName)
{
	std::vector<Channel>::iterator it = this->channels.begin();
	std::string reply = RPL_PART(client.getNickname(), client.getUsername(), channelName);

	while (it != this->channels.end())
	{
		
		if (isEqualStr(it->getName(), channelName) && it->clientInChannel(client.getNickname()))
		{
			it->removeFromChannel(client.getNickname(), reply);
			
			if (it->getUserCount() == 0)
			{
				channels.erase(it);
				std::cout << SERVER << BOLD_YELLOW << CHANNEL_DELETED(channelName) << RESET;
			}
			break ;
		}
		it++;
	}
	_removeChannelFromClient(client.getNickname(), channelName);
}

void Server::kickFromChannel(std::string& clientName, std::string& channelName, std::string& reply)
{
	std::vector<Channel>::iterator it = this->channels.begin();

	while (it != this->channels.end())
	{
		if (toUpperCase(it->getName()) == toUpperCase(channelName)
			&& it->clientInChannel(clientName))
		{
			it->removeFromChannel(clientName, reply);
			if (it->getUserCount() == 0)
			{
				this->channels.erase(it);
				std::cout << SERVER << BOLD_YELLOW << CHANNEL_DELETED(channelName) << RESET;
			}
			break ;	
		}
		it++;
	}
	_removeChannelFromClient(clientName, channelName);
}

void Server::_removeChannelFromClient(std::string clientName, std::string& channelName)
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
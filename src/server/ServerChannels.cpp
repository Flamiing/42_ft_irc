/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:13:49 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/28 16:29:58 by alaaouam         ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:06:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/18 12:52:46 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

void Client::addToJoinedChannels(Channel& channel)
{
	this->_joinedChannels.push_back(channel);
}

void Client::removeChannel(std::string& channel)
{
	std::vector<Channel>::iterator it = this->_joinedChannels.begin();

	while (it != this->_joinedChannels.end())
	{
		if (toUpperCase((*it).getName()) == toUpperCase(channel))
		{
			this->_joinedChannels.erase(it);
			break ;
		}
		it++;
	}
}

/* On user side */
bool Client::isConnectedToChannel(Channel& channel)
{
	for (std::vector<Channel>::iterator it = this->_joinedChannels.begin(); it != _joinedChannels.end(); it++)
		if (isEqualStr(it->getName(), channel.getName()))
			return true;
	return false;
}
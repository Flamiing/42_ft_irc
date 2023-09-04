/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDisconnection.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 15:11:16 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

void Channel::disconnectFromChannel(std::string client, const std::string& reply)
{
	std::vector<Client>::iterator it = this->_onlineUsers.begin();

	while (it != this->_onlineUsers.end())
	{
		if (it->getNickname() == client)
		{
			this->_onlineUsers.erase(it);
			this->_userCount--;
			break ;
		}
		it++;
	}
	_informOnlineUsers(reply);
}

void Channel::removeFromChannel(std::string client, const std::string& reply)
{
	std::vector<Client>::iterator it = this->_onlineUsers.begin();

	_informOnlineUsers(reply);
	while (it != this->_onlineUsers.end())
	{
		if (it->getNickname() == client)
		{
			this->_onlineUsers.erase(it);
			this->_userCount--;
			break ;
		}
		it++;
	}
}
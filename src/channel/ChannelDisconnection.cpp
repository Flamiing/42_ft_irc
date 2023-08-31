/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDisconnection.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 19:50:11 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

void Channel::disconnectFromChannel(std::string& client, const std::string& reply)
{
	std::vector<Client>::iterator it = this->_onlineUsers.begin();

	while (it != this->_onlineUsers.end())
	{
		if (it->getNickname() == client)
		{
			this->_onlineUsers.erase(it);
			break ;
		}
		it++;
	}
	_informOnlineUsers(reply);
}
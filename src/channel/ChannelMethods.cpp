/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMethods.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:33:47 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/08 16:35:22 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/* _GUILLE mover a archivo adecuado */
/* On user side */
bool Client::isConnectedToChannel(Channel& channel)
{
	for (std::vector<Channel>::iterator it = this->_joinedChannels.begin(); it != _joinedChannels.end(); it++)
		if (isEqualStr(it->getName(), channel.getName()))
			return true;
	return false;
}

/* On channel side */
bool Channel::isUserInChannel()
{
	for (std::vector<Client>::iterator it = this->_onlineUsers.begin(); it != _onlineUsers.end(); it++)
		if (isEqualStr(this->getName(), it->getNickname()))
			return true;
	return false;
}

bool Channel::isClientOperator(Client& client)
{
	return true;
	if (" " == client.getNickname()) /* _GUILLE check if its operator */
		return true;
	return false;
}


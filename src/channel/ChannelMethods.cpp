/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMethods.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:33:47 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/13 09:39:56 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

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


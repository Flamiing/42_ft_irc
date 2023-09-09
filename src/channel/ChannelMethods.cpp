/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMethods.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:33:47 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/09 17:53:31 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/* On channel side */
bool Channel::isUserInChannel()
{
	for (std::vector<Client>::iterator it = this->_onlineUsers.begin(); it != _onlineUsers.end(); it++)
		if (isEqualStr(this->getName(), it->getNickname()))
			return true;
	return false;
}



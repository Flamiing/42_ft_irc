/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMethods.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:33:47 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/08 14:04:41 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"
/* _GUILLE revisar si se usa */
bool Client::isConnectedToChannel(Channel& channel)
{
	std::string str;
	
	for (std::vector<Channel>::iterator it = this->_joinedChannels.begin(); it != _joinedChannels.end(); it++)
	{
		str = it->getName();
		if (!str.compare(channel.getName()))
			return true;
	}
	return false;
}
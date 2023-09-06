/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMethods.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:33:47 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/04 17:41:11 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

bool Client::checkChannel(Channel& channel)
{
	std::vector<Channel>::iterator it;
	
	std::string str;
	for (this->_joinedChannels.begin(); it != _joinedChannels.end(); it++)
	{
		str = it->getName();
		if (str.compare(channel.getName()))
			return true;
	}
	return false;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMethods.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:33:47 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/08 16:01:53 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

bool Client::isConnectedToChannel(Channel& channel)
{
	for (std::vector<Channel>::iterator it = this->_joinedChannels.begin(); it != _joinedChannels.end(); it++)
	{
		if (isEqualStr(it->getName(), channel.getName()))
			return true;
	}
	return false;
}
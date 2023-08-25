/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDisconnection.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/25 19:21:31 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

void Channel::disconnectFromChannel(std::string& client, int mode)
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();

	while (it != this->_onlineUsers.end())
	{
		if ((*it).getName() != client)
			send()
		if ((*it).getName() == client)
			this->_onlineUsers.pop(it);
		it++;
	}
}
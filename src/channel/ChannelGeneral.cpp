/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelGeneral.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:58:13 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 10:58:28 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Channel.hpp"

bool Channel::clientInChannel(std::string nickname)
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();

	while (it != this->_onlineUsers.end())
	{
		if (toUpperCase((*it).getNickname()) == toUpperCase(nickname))
			return true;
		it++;
	}
	return false;
}

void Channel::messageOnlineUsers(const std::string sender, const std::string& reply)
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();
	
	while (it != this->_onlineUsers.end())
	{
		if (toUpperCase(it->getNickname()) != toUpperCase(sender))
			send(it->getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
		it++;
	}
}
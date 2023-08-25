/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelJoinChannel.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:18:42 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/25 17:38:07 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

void Channel::_replyToNewUser(Client& client)
{
	std::string buffer = RPL_TOPIC(client.getNickname(), this->getName(), this->getTopic());
	buffer += RPL_NAMREPLY(client.getNickname(), "=", this->getName(), this->getOnlineUsersList());
	buffer += RPL_ENDOFNAMES(client.getNickname(), this->getName());
	
	send(client.getSocket(), buffer.c_str(), buffer.size(), 0);
}

void Channel::_informOnlineUsers(Client& client)
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();
	std::string buffer = RPL_USERJOINEDCHANNEL(client.getNickname(),
			client.getUsername(), this->getName());
	
	while (it != this->_onlineUsers.end())
	{
		send(it->getSocket(), buffer.c_str(), buffer.size(), 0);
		it++;
	}
}

void Channel::joinChannel(Client& client, std::string& key)
{
	std::string channelKey = this->getKey();
	
	if (channelKey.empty())
	{
		this->_onlineUsers.push_back(client);
		_informOnlineUsers(client);
		_replyToNewUser(client);
	}
	(void)key;
	//if (!channelKey.empty() && channelKey == key)
}
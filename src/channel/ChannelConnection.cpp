/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelConnection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:18:42 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 15:38:14 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

void Channel::_replyToNewUser(Client& client)
{
	std::string reply = RPL_TOPIC(client.getNickname(), this->getName(), this->getTopic());
	reply += RPL_NAMREPLY(client.getNickname(), "=", this->getName(), this->getOnlineUsersList());
	reply += RPL_ENDOFNAMES(client.getNickname(), this->getName());
	
	send(client.getSocket(), reply.c_str(), reply.size(), 0);
}

void Channel::_informOnlineUsers(const std::string& reply)
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();
	
	while (it != this->_onlineUsers.end())
	{
		send(it->getSocket(), reply.c_str(), reply.size(), 0);
		it++;
	}
}

void Channel::joinChannel(Client& client, std::string& keyName, std::string& buffer)
{
	std::string reply = RPL_USERJOINEDCHANNEL(client.getNickname(),
		client.getUsername(), this->getName());
	
	if (this->modes[MODE_CHANNEL_USER_LIMIT])
	{
		if (this->getUserCount() >= this->getLimit())
		{
			buffer = ERR_CHANNELISFULL(client.getNickname(), this->getName());
			return ;
		}
	}
	if (this->modes[MODE_CHANNEL_KEY] == false || !keyName.compare(this->getKey()))
	{
		this->_onlineUsers.push_back(client);
		_informOnlineUsers(reply);
		_replyToNewUser(client);
		client.addToJoinedChannels(*this);
	}
	else
		buffer = ERR_BADCHANNELKEY(client.getNickname(), this->getName());
	this->_userCount++;
}
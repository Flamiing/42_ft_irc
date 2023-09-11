/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannelConnection.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:49:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 18:55:23 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::addChannel(std::string channelName, std::string keyName, std::string operatorName)
{
	Channel newChannel(channelName, keyName);
	if (!keyName.empty())
		newChannel.modes[MODE_CHANNEL_KEY] = true;
	newChannel.addOperator(operatorName);
	this->channels.push_back(newChannel);
	
}

bool clientAlreadyConnected(std::string& channel, Client& client)
{
	for (size_t i = 0; i < client.getJoinedChannels().size(); i++)
	{
		if (isEqualStr(client.getJoinedChannels()[i].getName(), channel))
			return true;
	}
	return false;
}

void Server::connectToChannel(std::string& channel, Client& client, std::string& key, std::string& buffer)
{
	std::vector<Channel>::iterator it = this->channels.begin();

	while (it != this->channels.end())
	{
		if (isEqualStr(it->getName(), channel))
		{
			if (clientAlreadyConnected(channel, client))
				return ;
			if (client.getJoinedChannels().size() > MAX_CHANNELS_PER_CLIENT - 1)
			{
				buffer = ERR_TOOMANYCHANNELS(client.getNickname(), it->getName());
				return ;
			}
			else
			{
				it->joinChannel(client, key, buffer);
				return ;
			}
		}
		it++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannelConnection.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:49:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 14:55:03 by guilmira         ###   ########.fr       */
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


void Server::connectToChannel(std::string& channel, Client& client, std::string& key, std::string& buffer)
{
	std::vector<Channel>::iterator it = this->channels.begin();

	while (it != this->channels.end())
	{
		if (isEqualStr(it->getName(), channel))
		{
			it->joinChannel(client, key, buffer);
			return ;
		}
		it++;
	}
}
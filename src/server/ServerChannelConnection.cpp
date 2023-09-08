/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannelConnection.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:49:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 14:00:01 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::addChannel(std::string channelName, std::string keyName)
{
	Channel newChannel(channelName, keyName);
	if (!keyName.empty())
		newChannel.modes[MODE_CHANNEL_KEY] = true;
	this->channels.push_back(newChannel);
	std::cout << "SIZE" << channels.size() << std::endl;
}

void Server::connectToChannel(std::string& channel, Client& client, std::string& key, std::string& buffer)
{
	std::vector<Channel>::iterator it = this->channels.begin();

	while (it != this->channels.end())
	{
		if (toUpperCase(it->getName()) == toUpperCase(channel))
		{
			it->joinChannel(client, key, buffer);
			return ;
		}
		it++;
	}

	

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 23:11:42 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 08:23:35 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool notInChannel(Client& client, std::string& channelName)
{
	std::vector<Channel> channels = client.getJoinedChannels();
	std::vector<Channel>::const_iterator it = channels.begin();

	while (it != channels.end())
	{
		if ((*it).getName() == channelName)
			return false;
		it++;
	}
	return true;
}

bool findChannels(Client& client, std::vector<Channel> channels, std::vector<std::string>& channelsToFind)
{
	std::vector<std::string>::iterator toFind = channelsToFind.begin();
	std::string reply;
	size_t invalidChannels = 0;
	
	while (toFind != channelsToFind.end())
	{
		if (channelNotFound(channels, *toFind))
		{
			reply = ERR_NOSUCHCHANNEL(client.getNickname(), *toFind);
			send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
			invalidChannels++;
		}
		else if (notInChannel(client, *toFind))
		{
			reply = ERR_NOTONCHANNEL(client.getNickname(), *toFind);
			send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
			invalidChannels++;
		}
		reply = "";
		toFind++;
	}
	if (invalidChannels == channelsToFind.size())
		return false;
	return true;
}

bool channelNotFound(std::vector<Channel> channels, std::string channelToFind)
{
	std::vector<Channel>::const_iterator it = channels.begin();
	
	while (it != channels.end())
	{
		if (toUpperCase((*it).getName()) == toUpperCase(channelToFind))
			return false;
		it++;
	}
	return true;
}
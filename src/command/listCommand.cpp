/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:53:27 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 08:22:33 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void listAllChannels(std::vector<Channel>& channels, Client& client)
{
	std::vector<Channel>::iterator channel = channels.begin();
	std::string reply;
	
	reply = RPL_LISTSTART(client.getNickname());
	send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
	while (channel != channels.end())
	{
		if ((*channel).modes['p'] != true && (*channel).modes['s'] != true)
		{
			reply = RPL_LIST(client.getNickname(), channel->getName(),
				numberToString(channel->getUserCount()), channel->getTopic());
			send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
		}
		channel++;
	}
	reply = RPL_LISTEND(client.getNickname());
	send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
}

void listSpecifiedChannels(std::vector<Channel>& channels, std::vector<std::string>& channelsToFind, Client& client)
{
	std::vector<Channel>::iterator channel;
	std::vector<std::string>::iterator toFind = channelsToFind.begin();
	std::string reply;
	
	reply = RPL_LISTSTART(client.getNickname());
	send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
	while (toFind != channelsToFind.end())
	{
		channel = channels.begin();
		while (channel != channels.end())
		{
			if (toUpperCase(channel->getName()) == toUpperCase(*toFind)
				&& channel->modes['p'] != true && channel->modes['s'] != true)
			{
				reply = RPL_LIST(client.getNickname(), channel->getName(),
					numberToString(channel->getUserCount()), channel->getTopic());
				send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
			}
			channel++;
		}
		toFind++;
	}
	reply = RPL_LISTEND(client.getNickname());
	send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
}

void listCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::vector<std::string> channelsToFind;

	if (command.message.size() == 1)
		listAllChannels(server.channels, client);
	else
	{
		channelsToFind = getChannelNames(command.message[1], LIST);
		listSpecifiedChannels(server.channels, channelsToFind, client);
	}
}
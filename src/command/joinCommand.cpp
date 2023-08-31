/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 14:58:41 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool channelNotFound(std::vector<Channel>& channels, std::string channelToFind)
{
	std::vector<Channel>::const_iterator it = channels.begin();
	
	while (it != channels.end())
	{
		if ((*it).getName() == channelToFind)
			return false;
		it++;
	}
	return true;
}

static void joinChannel(Server& server, std::vector<Channel> channels, Client& client, std::vector<std::string>& message)
{
	if (channels.size() == 0 || channelNotFound(channels, message[1]))
		server.addChannel(message[1]);
	if (message.size() == 2)
		server.connectToChannel(message[1], client, "");
	//else if ()
	//else if (CHANNEL IS INVITE ONLY MODE)
	//	server.connectToChannel(message[1], client, message[2]);
}

static bool handleErrors(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (message.size() < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), message[0]);
		return true;
	}
	//else if (server.isBanned(client.getNickname(), message[1]))
	//	buffer = ERR_BANNEDFROMCHAN(client.getNickname(), message[1]);
	//else if ()
	//	buffer = ERR_INVITEONLYCHAN(client.getNickname(), message[1]);
	return false;
	(void)server;
}

void joinCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(server, client, buffer, command.message))
		return ;
	command.message[1].erase(0, 1);
	joinChannel(server, server.getChannels(), client, command.message);
} 

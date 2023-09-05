/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 13:47:18 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static void joinChannel(Server& server, std::vector<Channel> channels, Client& client, std::vector<std::string>& message)
{
	if (channels.size() == 0 || channelNotFound(channels, message[1]))
		server.addChannel(message[1]);
	if (message.size() == 2)
		server.connectToChannel(message[1], client, "");
	
	//else if (CHANNEL IS INVITE ONLY MODE)
	//	server.connectToChannel(message[1], client, message[2]);
}

static bool parserJoin(Command& command)
{
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (static_cast<int>(command.message.size()) < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.message[0]);
		return true;
	}
	return false;
}

void joinCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;	

	if (parserJoin(command))
		return ;
	if (server.isBanned(client, command.message[1]))
		buffer = ERR_BANNEDFROMCHAN(client.getNickname(), command.message[1]);
	//	buffer = ERR_INVITEONLYCHAN(client.getNickname(), message[1]); lista ccon usuarios invitados. comprobar y meter.
	joinChannel(server, server.getChannels(), client, command.message);
} 

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:44:22 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 15:26:21 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static std::string getQuitReply(Client& client, Command& command)
{
	std::string reply;
	
	if (command.message.size() > 1 && command.message[1][0] == ':')
		command.message[1].erase(0, 1);
	if (command.message.size() < 2 || command.message[1].empty())
		reply = RPL_QUITWITHNOMSG(client.getNickname(), client.getUsername());
	else
	{
		std::vector<std::string> remove;
		remove.push_back(command.cmd);
		remove.push_back(":");
		std::string messageToSend = getMessage(command.raw, remove);
		reply = RPL_QUIT(client.getNickname(), client.getUsername(), messageToSend);
	}
	return reply;
}

void quitCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;

	std::string reply = getQuitReply(client, command);
	
	server.disconnectClientFromChannels(client.getNickname(), reply);
	server.disconnect(server.pollSize);
}

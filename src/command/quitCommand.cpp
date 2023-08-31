/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:44:22 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 16:06:25 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/Server.hpp"

std::string getQuitReply(Client& client, Command& command)
{
	std::string reply;
	
	if (command.message.size() < 2)
		reply = RPL_QUITWITHNOMSG(client.getNickname(), client.getUsername());
	else
	{
		std::vector<std::string> remove;
		remove.push_back(command.cmd);
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
	
	client.disconnectChannels(reply);
	server.disconnect(client.getPollFDPos());
}

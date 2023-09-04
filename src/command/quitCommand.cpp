/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:44:22 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 13:21:46 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static std::string getQuitReply(Client& client, Command& command)
{
	std::string reply;
	
	if (command.message.size() < 2 || command.message[1].empty())
		reply = RPL_QUITWITHNOMSG(client.getNickname(), client.getUsername());
	else
	{
		std::string messageToSend = getMessageToSend(command, 1);
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

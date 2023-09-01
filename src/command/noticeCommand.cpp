/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noticeCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:18:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 15:26:16 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"

static bool handleErrors(Client& client, std::string& buffer, Command& command)
{
	if (command.message.size() == 1)
	{
		buffer = ERR_NORECIPIENT(client.getNickname(), command.cmd);
		return true;
	}
	else if (command.message.size() == 2)
	{
		buffer = ERR_NOTEXTTOSEND(client.getNickname());
		return true;
	}
	return false;
}

void noticeCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(client, buffer, command))
		return ;
	std::vector<std::string> remove;
	remove.push_back(command.cmd);
	remove.push_back(command.message[1]);
	std::string messageToSend = getMessage(command.raw, remove);
	std::string rawNickname = server.getRawNickname(command.message[1]);
	std::string reply = MSG_NOTICE(client.getNickname(), client.getUsername(), rawNickname, messageToSend);
	int recipientSocket = server.getSocketByNickname(rawNickname);
	send(recipientSocket, reply.c_str(), reply.size(), 0);
}
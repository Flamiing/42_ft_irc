/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noticeCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:18:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 19:15:47 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands.hpp"
#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/IRCMessage.hpp"

static bool handleErrors(Client& client, std::string& buffer, IRCMessage& messageIRC)
{
	if (messageIRC.vector.size() == 1)
	{
		buffer = ERR_NORECIPIENT(client.getNickname(), messageIRC.cmd);
		return true;
	}
	else if (messageIRC.vector.size() == 2)
	{
		buffer = ERR_NOTEXTTOSEND(client.getNickname());
		return true;
	}
	return false;
}

void noticeCommand(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC)
{
	if (handleErrors(client, buffer, messageIRC))
		return ;
	std::vector<std::string> remove;
	remove.push_back(messageIRC.cmd);
	remove.push_back(messageIRC.vector[1]);
	std::string messageToSend = getMessage(messageIRC.raw, remove);
	std::string reply = MSG_NOTICE(client.getNickname(), client.getUsername(), messageIRC.vector[1], messageToSend);
	int recipientSocket = server.getSocketByNickname(messageIRC.vector[1]);
	send(recipientSocket, reply.c_str(), reply.size(), 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:44:22 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 13:31:08 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/Server.hpp"
#include "../../inc/IRCMessage.hpp"

std::string getQuitReply(Client& client, IRCMessage& messageIRC)
{
	std::string reply;
	
	if (messageIRC.vector.size() < 2)
		reply = RPL_QUITWITHNOMSG(client.getNickname(), client.getUsername());
	else
	{
		std::vector<std::string> remove;
		remove.push_back(messageIRC.cmd);
		std::string messageToSend = getMessage(messageIRC.raw, remove);
		reply = RPL_QUIT(client.getNickname(), client.getUsername(), messageToSend);
	}
	return reply;
}

void quitCommand(Server& server, Client& client, IRCMessage& messageIRC)
{
	std::string reply = getQuitReply(client, messageIRC);
	
	client.disconnectChannels(reply);
	server.disconnect(client.getPollFDPos());
}
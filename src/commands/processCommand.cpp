/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/25 19:46:33 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/commands.hpp"

static void commandProcessor(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC)
{
	if (messageIRC.cmd == JOIN)
		joinCommand(server, client, buffer, messageIRC.vector);
	else
		buffer = ERR_UNKNOWNCOMMAND(client.getNickname(), messageIRC.cmd);
//	else if (message[0] == PRIVMSG)
//		privmsgCommand(client, buffer, message);
//	else if (message[0] == NOTICE)
//		noticeCommand(client, buffer, message);
//	else if (message[0] == HELP)
//		helpCommand(client, buffer, message);
//	else if (message[0] == OPER)
//		operCommand(client, buffer, message);
//	else if (message[0] == KICK)
//		kickCommand(client, buffer, message);
//	else if (message[0] == TOPIC)
//		topicCommand(client, buffer, message);
//	else if (message[0] == QUIT)
//		quitCommand(client, buffer, message);
}

void processCommand(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC)
{
	if (messageIRC.cmd == PASS)
		passCommand(server, client, buffer, messageIRC.vector);
	else if (client.getPassAuth() == true && messageIRC.cmd == USER)
		userCommand(client, buffer, messageIRC.vector);
	else if (client.getPassAuth() == true && messageIRC.cmd == NICK)
		nickCommand(server, client, buffer, messageIRC.vector);
	else if (messageIRC.cmd == PONG)
		return ;
	else if (client.getAuth() == true)
		commandProcessor(server, client, buffer, messageIRC);
	else
	{
		if (client.getAuth() == true)
			buffer = ERR_NOTREGISTERED(client.getNickname());
		else
			buffer = ERR_NOTREGISTERED(client.getWrongNickname());
	}
}
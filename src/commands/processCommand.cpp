/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 14:43:41 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/commands.hpp"

#include "../../inc/Command.hpp"

//static void helpCommand(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC)
static void helpCommand(Client& client, std::string& buffer)
{
	buffer = RPL_HELP(client.getNickname());
}

/* static void quitCommand(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC)
{
	std::string user_message;
	std::string full_message;

	full_message = messageIRC.raw;
	//full_message = messageIRC.getRaw();

	size_t clientFd;
	clientFd = client.getSocket();

	user_message = full_message.substr(full_message.find(" "));
	buffer = RPL_QUIT(client.getNickname(), client.getUsername(), user_message);
	server._disconnect(&clientFd);
} */

/* else if (messageIRC.cmd == QUIT)
		quitCommand(server, client, buffer, messageIRC); */



static void commandProcessor(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC)
{

	if (messageIRC.cmd == JOIN)
		joinCommand(server, client, buffer, messageIRC.vector);
	else if (messageIRC.cmd == HELP)
		helpCommand(client, buffer);
	else
		buffer = ERR_UNKNOWNCOMMAND(client.getNickname(), messageIRC.cmd);
/* 	else if (messageIRC.cmd == PRIVMSG)
		privmsgCommand(client, buffer, message);
	else if (messageIRC.cmd == NOTICE)
		noticeCommand(client, buffer, message);
	else if (messageIRC.cmd == OPER)
		operCommand(client, buffer, message);
	else if (messageIRC.cmd == KICK)
		kickCommand(client, buffer, message);
	else if (messageIRC.cmd == TOPIC)
		topicCommand(client, buffer, message); */
	
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 12:33:32 by guilmira         ###   ########.fr       */
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

	/* 	std::map<std::string, Command *>::iterator it;
	it = mapCom.find(messageIRC.cmd);
	if (it == mapCom.end())
		return ; //no es comando
	else
	{
		mapCom[messageIRC.cmd]->executeCom();
	} */

	mapComm
	if (messageIRC.cmd == JOIN)
		joinCommand(server, client, buffer, messageIRC.vector);
	else if (messageIRC.cmd == HELP)
		helpCommand(client, buffer);
	else
		buffer = ERR_UNKNOWNCOMMAND(client.getNickname(), messageIRC.cmd);
	
}

//_GUILLE metodo de server
void fillMap(std::map<std::string, customFunctionType>& mapCommand)
{
	mapCommand[PASS] = &passCommand;
	mapCommand[USER] = &userCommand;
	mapCommand[NICK] = &nickCommand;
	mapCommand[JOIN] = &joinCommand;
	mapCommand[PRIVMSG] = &privmsgCommand;
	mapCommand[QUIT] = &quitCommand;
}

void processCommand(Server& server, Client& client, std::string& buffer, Command& command, IRCMessage& messageIRC)
{

	std::map<std::string, customFunctionType> mapCommand;

	fillMap(mapCommand);
	if (!command.cmd.compare(PASS))
		mapCommand[PASS](command);
	else if (client.getPassAuth() == true && !command.cmd.compare(USER))
		mapCommand[USER](command);
	else if (client.getPassAuth() == true && !command.cmd.compare(NICK))
		mapCommand[NICK](command);
	else if (!command.cmd.compare(PONG))
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
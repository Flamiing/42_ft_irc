/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/24 21:25:11 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/commands.hpp"

static void commandProcessor(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
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
//	else if (message[0] == JOIN)
//		joinCommand(client, buffer, message);
//	else if (message[0] == TOPIC)
//		topicCommand(client, buffer, message);
//	else if (message[0] == QUIT)
//		quitCommand(client, buffer, message);
	(void)server;
	buffer = ERR_UNKNOWNCOMMAND(client.getNickname(), message[0]);
}

void processCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (message[0] == PASS)
		passCommand(server, client, buffer, message);
	else if (client.getPassAuth() == true && message[0] == USER)
		userCommand(client, buffer, message);
	else if (client.getPassAuth() == true && message[0] == NICK)
		nickCommand(server, client, buffer, message);
	else if (client.getAuth() == true)
		commandProcessor(server, client, buffer, message);
	else
		buffer = ERR_NOTREGISTERED(client.getNickname());
}
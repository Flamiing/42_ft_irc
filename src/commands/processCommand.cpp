/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/23 16:17:39 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/commands.hpp"

void processCommand(Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (message[0] == USER)
		userCommand(client, buffer, message);
	else if (message[0] == NICK)
		nickCommand(client, buffer, message);
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
//	else
//		std::strcpy(buffer, INVALID_CMD);
}
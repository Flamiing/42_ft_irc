/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:27:35 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 14:35:30 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool handleErrors(Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (client.getAuth() == true)
	{
		buffer = ERR_ALREADYREGISTRED(client.getNickname());
		return true;
	}
	if (message.size() < 6)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), message[0]);
		return true;
	}
	return false;
}

void userCommand(Command &command)
{
	if (handleErrors(*command.client, *command.buffer, command.message))
		return ;
	command.client->setUserAuth(true);
	command.client->setUsername(command.message[1]);
	std::string fullName = command.message[4].c_str() + 1;
	fullName += " " + command.message[5];
	command.client->setFullName(fullName);
	if (command.client->getAuth() == true)
		*command.buffer = RPL_WELCOME(command.client->getNickname());
}

/* void userCommand(Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (handleErrors(client, buffer, message))
		return ;
	client.setUserAuth(true);
	client.setUsername(message[1]);
	std::string fullName = message[4].c_str() + 1;
	fullName += " " + message[5];
	client.setFullName(fullName);
	if (client.getAuth() == true)
		buffer = RPL_WELCOME(client.getNickname());
} */
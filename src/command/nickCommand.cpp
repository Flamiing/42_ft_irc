/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:45:31 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 12:21:02 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands.hpp"
#include "../../inc/Server.hpp"
#include <cctype>
#include <map> /* _GUILLE - este map dberia ir aqui solo? */
#include "../../inc/Command.hpp"

static bool invalidNickname(std::string& nickname)
{
	size_t pos = 0;
	
	if (!nickname.empty() && !isalpha(nickname[0])
		&& nickname[0] != '_')
		return true;
	while (pos < nickname.size())
	{
		if (!isalnum(nickname[pos]) && nickname[pos] != '-'
			&& nickname[pos] != '_')
			return true;
		pos++;
	}
	return false;
}

static bool nicknameInUse(std::map<int, Client> clients, std::string& nickname)
{
	std::map<int, Client>::const_iterator it = clients.begin();

	while (it != clients.end())
	{
		if (it->second.getNickname() == nickname)
			return true;
		it++;
	}
	return false;
}

static bool handleErrors(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (message.size() < 2 || message[1].empty() || message[1] == ":")
	{
		buffer = ERR_NONICKNAMEGIVEN(client.getNickname());
		return true;
	}
	else if (nicknameInUse(server.getClients(), message[1]))
	{
		buffer = ERR_NICKNAMEINUSE(client.getNickname(), message[1]);
		return true;
	}
	else if (invalidNickname(message[1]))
	{
		buffer = ERR_ERRONEUSNICKNAME(client.getNickname(), message[1]);
		if (client.getAuth() == false)
			client.setWrongNickname(message[1]);
		return true;
	}
	return false;
}

void nickCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
	bool firstConnection = false;
	
	if (handleErrors(server, client, buffer, message))
		return ;
	if (client.getNickAuth() == true)
		buffer = RPL_NICKNAMECHANGED(client.getNickname(), client.getUsername(), message[1]);
	else
		firstConnection = true;
	client.setNickname(message[1]);
	client.setNickAuth(true);
	if (firstConnection && client.getAuth() == true)
		buffer = RPL_WELCOME(client.getNickname());
}


void nickCommand(Command& command)
{
	bool firstConnection = false;
	
	if (handleErrors(*command.server, *command.client, *command.buffer, command.message))
		return ;
	if (command.client->getNickAuth() == true)
		*command.buffer = RPL_NICKNAMECHANGED(command.client->getNickname(), command.client->getUsername(), command.message[1]);
	else
		firstConnection = true;
	command.client->setNickname(command.message[1]);
	command.client->setNickAuth(true);
	if (firstConnection && command.client->getAuth() == true)
		*command.buffer = RPL_WELCOME(command.client->getNickname());
}
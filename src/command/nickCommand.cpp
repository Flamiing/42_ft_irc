/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:45:31 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/17 00:41:53 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool invalidNickname(std::string& nickname)
{
	if (!nickname.empty() && !isalpha(nickname[0]) && nickname[0] != '_' && nickname[0] != '['
		&& nickname[0] != ']' && nickname[0] != '{' && nickname[0] != '}')
		return true;
	return false;
}

static bool nicknameInUse(std::map<int, Client> clients, std::string& nickname)
{
	std::map<int, Client>::const_iterator it = clients.begin();

	while (it != clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(nickname))
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
	else if (nicknameInUse(server.getClients(), message[1])
				&& toUpperCase(message[1]) != toUpperCase(client.getNickname()))
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

static std::string getNewNickname(std::string nickname)
{
	std::string newNickname;
	size_t pos = 0;
	
	while (pos < nickname.size() && (isalnum(nickname[pos]) || nickname[pos] == '_' || nickname[pos] == '['
				|| nickname[pos] == ']' || nickname[pos] == '{' || nickname[pos] == '}' || nickname[pos] == '-'))
		pos++;
	return newNickname = nickname.substr(0, pos);
}

void nickCommand(Command& command)
{
	bool firstConnection = false;
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;
	std::string newNickname;
	
	if (handleErrors(server, client, buffer, command.message))
		return ;
	newNickname = getNewNickname(command.message[1].substr(0, 12));
	if (toUpperCase(newNickname) == toUpperCase(client.getNickname()))
		return ;
	if (client.getNickAuth() == true)
		buffer = RPL_NICKNAMECHANGED(client.getNickname(), client.getUsername(), newNickname);
	else
		firstConnection = true;
	client.setNickname(newNickname);
	client.setNickAuth(true);
	if (firstConnection && client.getAuth() == true)
		buffer = RPL_WELCOME(client.getNickname());
}
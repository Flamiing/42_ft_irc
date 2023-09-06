/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:55:48 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/06 07:29:01 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool hasWhiteSpace(const std::string& str)
{
	size_t pos = 0;
	
	while (pos != str.size())
	{
		if (isspace(str[pos]))
			return true;
		pos++;
	}
	return false;
}

static std::string removeFromSpace(const std::string& str)
{
	std::string newString;
	size_t pos = 0;

	while (pos < str.size())
	{
		if (isspace(str[pos]))
			break ;
		newString.push_back(str[pos]);
		pos++;
	}
	if (pos == 0)
		return str;
	return newString;
}

/* _GUILLE cambio parametro de la funcion para reutilizarla */
std::vector<std::string> getChannels(std::string& raw, std::string commandName)
{
	std::vector<std::string> remove;
	remove.push_back(commandName);
	std::string commaSeparated = getMessage(raw, remove);
	commaSeparated = trimSpaces(commaSeparated);
	std::vector<std::string> channels = splitString(commaSeparated, ',');
	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator end = channels.end();
	bool whiteSpaceFound = false;
	
	while (it != end)
	{
		if (hasWhiteSpace(*it))
		{
			whiteSpaceFound = true;
			*it = removeFromSpace(*it);
			it++;
			break ;
		}
		it++;
	}
	if (whiteSpaceFound)
		channels.erase(it, end);
	return channels;
}

static void partFromChannels(Server& server, Client& client, std::vector<std::string>& channels)
{
	std::vector<std::string>::iterator channel = channels.begin();
	
	while (channel != channels.end())
	{
		server.partFromChannel(client, *channel);
		channel++;
	}
}

void partCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;
	std::vector<std::string> channels = getChannels(command.raw, PART);

	if (command.message.size() < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.cmd);
		return ;
	}
	else if (!findChannels(client, server.channels, channels))
		return ;
	partFromChannels(server, client, channels);
}
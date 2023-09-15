/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:27:35 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/14 17:26:05 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool invalidUsername(std::string& username)
{
	size_t pos = 0;
	
	if (!username.empty() && !isalpha(username[0]))
		return true;
	while (pos < username.size())
	{
		if (!isalnum(username[pos]) && username[pos] != '-'
			&& username[pos] != '_')
			return true;
		pos++;
	}
	return false;
}

static bool handleErrors(Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (client.getAuth() == true)
	{
		buffer = ERR_ALREADYREGISTRED(client.getNickname());
		return true;
	}
	if (message.size() < 5)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), message[0]);
		return true;
	}
	if (invalidUsername(message[1]))
	{
		buffer = ERR_INVALIDUSERNAME(client.getNickname());
		return true;
	}
	return false;
}

static std::string getFullName(Command& command, size_t nameStart)
{
	std::vector<std::string> remove;
	std::string fullName;
	remove.push_back(command.cmd);
	remove.push_back(command.message[1]);
	remove.push_back(command.message[2]);
	remove.push_back(command.message[3]);
	
	if (command.message[nameStart][0] != ':')
		return command.message[command.message.size() - 1];
	else
		fullName = getMessage(command.raw, remove);
	if (fullName[0] == ':')
		fullName.erase(0, 1);
	return fullName;
}

void userCommand(Command &command)
{	
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(client, buffer, command.message))
		return ;
	client.setUserAuth(true);
	client.setUsername(command.message[1]);
	std::string fullName = getFullName(command, 4);
	client.setFullName(fullName);
	if (client.getAuth() == true)
		buffer = RPL_WELCOME(client.getNickname());
}

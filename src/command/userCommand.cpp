/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:27:35 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 15:08:10 by guilmira         ###   ########.fr       */
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
	if (message.size() < 6)
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

void userCommand(Command &command)
{	
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(client, buffer, command.message))
		return ;
	client.setUserAuth(true);
	client.setUsername(command.message[1]);
	std::string fullName = command.message[4].c_str() + 1;
	fullName += " " + command.message[5];
	client.setFullName(fullName);
	if (client.getAuth() == true)
		buffer = RPL_WELCOME(client.getNickname());
}

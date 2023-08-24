/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:45:31 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/24 21:40:51 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands.hpp"
#include "../../inc/Server.hpp"
#include <cctype>
#include <map>

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

static bool handleErrors(Server& server, Client& client, std::string& buffer, std::string& newNickname)
{
	if (newNickname == ":" || newNickname.empty())
	{
		buffer = ERR_NONICKNAMEGIVEN(client.getNickname());
		return true;
	}
	else if (nicknameInUse(server.getClients(), newNickname))
	{
		buffer = ERR_NICKNAMEINUSE(client.getNickname(), newNickname);
		return true;
	}
	else if (invalidNickname(newNickname))
	{
		buffer = ERR_ERRONEUSNICKNAME(client.getNickname(), newNickname);
		return true;
	}
	return false;
}

void nickCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
	bool firstConnection = false;
	
	if (handleErrors(server, client, buffer, message[1]))
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
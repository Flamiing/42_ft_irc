/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:45:31 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/24 19:26:17 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands.hpp"
#include <cctype>

static bool invalidNickname(std::string& nickname)
{
	if (!nickname.empty() && !isalpha(nickname[0]))
		return true;
	size_t pos = 0;
	while (pos < nickname.size())
	{
		if (!isalnum(nickname[pos]))
			return true;
		pos++;
	}
	return false;
}

static bool handleErrors(Client& client, std::string& buffer, std::string& newNickname)
{
	if (newNickname == ":" || newNickname.empty())
	{
		buffer = ERR_NONICKNAMEGIVEN(client.getNickname());
		return true;
	}
	else if (invalidNickname(newNickname))
	{
		buffer = ERR_ERRONEUSNICKNAME(client.getNickname(), newNickname);
		return true;
	}
	return false;
}

void nickCommand(Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (handleErrors(client, buffer, message[1]))
		return ;
	if (client.getNickAuth() == true)
		buffer = RPL_NICKNAMECHANGED(client.getNickname(), client.getUsername(), message[1]);
	client.setNickname(message[1]);
	client.setNickAuth(true);
}
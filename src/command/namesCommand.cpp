/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   namesCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:35:00 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/08 18:05:46 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static std::string processRaw(std::string raw)
{
	size_t count = 0;
	raw.erase(0, raw.find(NAMES) + 5);
	size_t	pos = raw.find_first_not_of(" ");
	raw.erase(0, pos);
	for (size_t i = count; i < raw.size(); i++)
	{
		if (raw[i] == ',')
		{
			if (i + 1 == raw.size())
				return raw.substr(0, i);
			if (std::isspace(raw[i + 1]))
				return raw.substr(0, i);
			if (raw[i + 1] != '#' && raw[i + 1] != '&')
				return raw.substr(0, i);
		}
	}
	return raw;
}

static void printNames(Client& client, Channel& channel)
{
	std::string reply = RPL_NAMREPLY(client.getNickname(), "=", channel.getName(), channel.getOnlineUsersList());
	reply += RPL_ENDOFNAMES(client.getNickname(), channel.getName());
	send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
}

static void sendName(Command& command, std::string& channelName)
{
	Server&						server = *command.server;
	std::vector<Channel>&		channel = server.channels;
	Client&						client = *command.client;

	for (size_t i = 0; i != channel.size(); i++)
		if (isEqualStr(channel[i].getName(), channelName))
			printNames(client, channel[i]);
}

void namesCommand(Command& command)
{
	std::vector<std::string>	channelNames;
	std::string					processed;

	processed = processRaw(command.raw);
	channelNames = splitString(processed, ',');
	for (size_t i = 0; i != channelNames.size(); i++)
		sendName(command, channelNames[i]);
	return ;
}
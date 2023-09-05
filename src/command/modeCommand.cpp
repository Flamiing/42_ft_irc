/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:27:39 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/05 21:14:07 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

/* static bool parserMode(Command& command)
{
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (static_cast<int>(command.message.size()) < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.message[0]);
		return true;
	}
	if (static_cast<int>(command.message.size()) > 3)
	{
		buffer = displayMsg("666", "too many parameters", client.getNickname());
		return true;
	}
	return false;
} */

// :Pipera.RO.EU.Undernet.Org 324 worbam #test2 +pmtnlk 10 * //// El asterisco es cuando hay key y el 10 es cuando hay limit

static bool handleErrors(Server& server, Client& client, std::string& buffer, Command& command)
{
	if (command.message.size() == 1)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.cmd);
		return true;
	}
	else if (channelNotFound(server.channels, command.message[1]))
	{
		buffer = ERR_NOSUCHCHANNEL(client.getNickname(), command.message[1]);
		return true;
	}
	return false;
}

static bool hasToBeReplied(char mode)
{
	size_t pos = 0;
	char modesList[] = 
	{
		MODE_CHANNEL_OPERATOR,
		MODE_CHANNEL_BANNED,
		MODE_CHANNEL_SPEAK_ABILITY,
		MODE_CHANNEL_KEY
	};

	while (pos < 4)
	{
		if (mode == modesList[pos])
			return false;
		pos++;
	}
	return true;
}

static void replyChannelModes(Channel& channel, Client& client)
{
	std::map<char, bool>::iterator it = channel.modes.begin();
	std::string reply;
	std::string modesToReturn = "+";
	bool hasKey = false;
	bool hasLimit = false;

	while (it != channel.modes.end())
	{
		if (it->second == true && hasToBeReplied(it->first))
			modesToReturn += it->first;
		if (it->first == MODE_CHANNEL_KEY && it->second == true)
			hasKey = true;
		if (it->first == MODE_CHANNEL_USER_LIMIT && it->second == true)
			hasLimit = true;
		it++;
	}
	if (hasKey)
		modesToReturn += 'k';
	if (hasLimit)
		modesToReturn += " " + numberToString(channel.getLimit());
	if (hasKey)
		modesToReturn += " *";
	reply = RPL_CHANNELMODEIS(client.getNickname(), channel.getName(), modesToReturn);
	reply += RPL_CREATIONTIME(client.getNickname(), channel.getName(), channel.creationTime);
	send(client.getSocket(), reply.c_str(), reply.size(), 0);
}

void modeCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(server, client, buffer, command))
		return ;
	Channel channel = server.getChannelByName(command.message[1]);
	if (command.message.size() == 2)
		replyChannelModes(channel, client);
}
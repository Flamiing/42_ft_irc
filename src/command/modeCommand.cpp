/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:27:39 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/12 09:23:22 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

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
		MODE_CHANNEL_SPEAK_ABILITY
	};

	while (pos < 3)
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
	if (hasLimit)
		modesToReturn += " " + numberToString(channel.getLimit());
	if (hasKey)
		modesToReturn += " *";
	reply = RPL_CHANNELMODEIS(client.getNickname(), channel.getName(), modesToReturn);
	reply += RPL_CREATIONTIME(client.getNickname(), channel.getName(), channel.creationTime);
	send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
}

static size_t handleModesWithParams(Channel& channel, Client& client, std::string& modes, std::vector<std::string>& message, size_t currentMsg)
{
	size_t pos = 0;
	size_t argPos = 1;
	bool action = MODE_CHANNEL_ADD;
	
	while (pos < modes.size())
	{
		if (modes[pos] == SYMBOL_MINUS)
			action = MODE_CHANNEL_REMOVE;
		else if (modes[pos] == SYMBOL_PLUS)
			action = MODE_CHANNEL_ADD;
		if (modes[pos] == 'o' || modes[pos] == 'k' || modes[pos] == 'v'
			|| modes[pos] == 'l' || modes[pos] == 'b')
		{
			if ((currentMsg + argPos) < message.size())
				channel.setMode(client, modes[pos], message[currentMsg + argPos], action);
			else
				channel.setMode(client, modes[pos], NOPARAMETER, action);
			if (currentMsg != (message.size() - 1) && (currentMsg + argPos) < message.size())
				argPos++;
		}
		pos++;
	}
	return argPos;
}

void handleNormalModes(Channel& channel, Client& client, std::string& modes)
{
	size_t pos = 0;
	bool action = MODE_CHANNEL_ADD;

	while (pos < modes.size())
	{
		if (modes[pos] == SYMBOL_MINUS)
			action = MODE_CHANNEL_REMOVE;
		else if (modes[pos] == SYMBOL_PLUS)
			action = MODE_CHANNEL_ADD;
		if (modes[pos] != 'o' && modes[pos] != 'k' && modes[pos] != 'v'
			&& modes[pos] != 'l' && modes[pos] != 'b')
			channel.setMode(client, modes[pos], NOPARAMETER, action);
		pos++;
	}
}

static void modifyChannelModes(Channel& channel, Client& client, std::vector<std::string>& message)
{
	std::vector<std::string>::iterator it = message.begin() + 2;
	size_t pos = 2;
	size_t skips;
	
	while (it != message.end())
	{
		skips = handleModesWithParams(channel, client, *it, message, pos);
		handleNormalModes(channel, client, *it);
		pos += skips;
		it += skips;
	}
}

void modeCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(server, client, buffer, command))
		return ;
	Channel& channel = server.getChannelByName(command.message[1]);
	if (command.message.size() == 2)
		replyChannelModes(channel, client);
	else if (command.message.size() > 2)
		modifyChannelModes(channel, client, command.message);
}
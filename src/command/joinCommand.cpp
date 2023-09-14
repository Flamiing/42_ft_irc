/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/14 09:23:43 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool checkInvitation(Server& server, std::string& channelName, std::string userName)
{
	std::vector<Channel>&	channels = server.channels;
	std::vector<std::string> invitedUsers;

	for (size_t i = 0; i < channels.size(); i++)
	{
		if (isEqualStr(channels[i].getName(), channelName))
		{
			invitedUsers = channels[i].getInvitedUsers();
			if (channels[i].modes[MODE_CHANNEL_INVITE_ONLY] == true)
			{
				for (std::vector<std::string>::iterator it = invitedUsers.begin(); it != invitedUsers.end(); it++)
					if (isEqualStr(userName, *it))
						return true;
				return false;
			}
			else
				return true;
		}
	}
	return true;
}

static void joinChannel(Command& command, std::string& channelName, std::string& keyName, std::string& buffer)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::vector<Channel>&		channels = server.channels;

	if (client.getJoinedChannels().size() > MAX_CHANNELS_PER_CLIENT - 1)
	{
		buffer = ERR_TOOMANYCHANNELS(client.getNickname(), channelName);
		return ;
	}
	if (channels.size() == 0 || channelNotFound(channels, channelName))
		server.addChannel(channelName, keyName, client.getNickname());
	if (!checkInvitation(server, channelName, client.getNickname()))
	{
		buffer = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
		return ;
	}
	server.connectToChannel(channelName, client, keyName, buffer);
}

/* _GUILLE cuando creas canal no eres channel op en el lime */
static bool parserJoin(Command& command)
{
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (static_cast<int>(command.message.size()) < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.message[0]);
		return true;
	}
	return false;
}

/* 	
	Rule 0 - Erase the command
	Rule 1 - Cant end in comma.
	Rule 2 - After a comma, there cant be a space. if there is, is not evaluated into the prompt.
	Rule 3 - no channels without # or & */
static std::string processRaw(std::string raw)
{
	bool flag = false;
	size_t count = 0;

	raw.erase(0, raw.find(JOIN) + 4);	
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
		}
			flag = true;
		if (!flag && raw[i] == ',')
				if (raw[i + 1] != '#' && raw[i + 1] != '&')
					return raw.substr(0, i);
	}
	return raw;
}

void	getVectors(std::vector<std::string>& channelNames, std::vector<std::string>& keyNames, std::string processed)
{
	std::string channels;
	std::string keys;
	size_t count;

	for (count = 0; count < processed.size(); count++)
		if (std::isspace(processed[count]))
			break;
	channels = processed.substr(0, count);
	channelNames = splitString(channels, ',');
	if (count != processed.size())
	{
		keys = processed.substr(count + 1);
		keyNames = splitString(keys, ',');
	}
	else
		keys = "";
}

static void	lexerJoin(std::vector<std::string>& channelNames, std::vector<std::string>& keyNames, std::string raw)
{
	std::string processed;

	processed = processRaw(raw);
	getVectors(channelNames, keyNames, processed);
	size_t size = channelNames.size();
	size_t sizeKey = keyNames.size();
	for (size_t i = 0; i < size - sizeKey; i++)
		keyNames.push_back("");
}

void joinCommand(Command& command)
{
	std::string&				buffer = *command.buffer;	
	std::vector<std::string>	channelNames;
	std::vector<std::string>	keyNames;

	if (parserJoin(command))
		return ;
	lexerJoin(channelNames, keyNames, command.raw);
	for (size_t i = 0; i != channelNames.size(); i++)
	{
		if (i == 0 && !channelNames[0].empty())
		{
			if (channelNames[0][0] != '#')
			{
				buffer = ERR_NOSUCHCHANNEL(command.client->getNickname(), channelNames[0]);
				return ;
			}
		}
		if (command.server->isBanned(*command.client, channelNames[i]))
			buffer = ERR_BANNEDFROMCHAN(command.client->getNickname(), channelNames[i]);
		else
			joinChannel(command, channelNames[i], keyNames[i], buffer);
	}
}

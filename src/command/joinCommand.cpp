/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/07 12:52:53 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"


static void joinChannel(Command& command, std::string& channelName, std::string& keyName, std::string& buffer)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::vector<Channel>&		channels = server.channels;

	if (channels.size() == 0 || channelNotFound(channels, channelName))
		server.addChannel(channelName, keyName);
	server.connectToChannel(channelName, client, keyName, buffer);

	//else if (CHANNEL IS INVITE ONLY MODE)
	//	server.connectToChannel(message[1], client, message[2]);

}

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

void pstr(std::vector<std::string>& channelNames, std::vector<std::string>& keyNames)
{
std::vector<std::string>::iterator it = channelNames.begin();
	std::vector<std::string>::iterator it1 = keyNames.begin();

	while (it != channelNames.end())
	{
		std::cout << "name: " << *it << std::endl;
		it++;	
	}
	while (it1 != keyNames.end())
	{
		std::cout << "key: " << *it1 << std::endl;
		it1++;
	}
}

/* 	
	Rule 0 - Erase the command
	Rule 1 - Cant end in comma.
	Rule 2 - After a comma, there cant be a space. if there is, is not evaluated into the prompt.
	Rule 3 - no channels without # or & */
std::string processRaw(std::string raw)
{
	bool flag = false;
	size_t count = 0;

	raw.erase(0, raw.find(JOIN) + 4);	
	size_t	pos = raw.find_first_not_of(" ");
	raw.erase(0, pos);
	for (size_t i = count; i < raw.size(); i++)
	{
		if (raw[i] == ',')
			if (i + 1 == raw.size())
				return raw.substr(0, i);
		if (raw[i] == ',')
				if (std::isspace(raw[i + 1]))
					return raw.substr(0, i);
		if (raw[i] == ' ')
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
	keys = processed.substr(count + 1);
	channelNames = splitString(channels, ',');
	keyNames = splitString(keys, ',');
}


void	lexerJoin(std::vector<std::string>& channelNames, std::vector<std::string>& keyNames, std::string raw)
{
	std::string processed;

	processed = processRaw(raw);
	getVectors(channelNames, keyNames, processed);
	size_t size = channelNames.size();
	size_t sizeKey = keyNames.size();
	for (size_t i = 0; i < size - sizeKey; i++)
		keyNames.push_back("");
	pstr(channelNames,keyNames);
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
		if (command.server->isBanned(*command.client, channelNames[i]))
			buffer = ERR_BANNEDFROMCHAN(command.client->getNickname(), channelNames[i]);
		else
			joinChannel(command, channelNames[i], keyNames[i], buffer);
	}

	/* std::cout << "HERE" << std::endl;
	for (size_t i = 0; i < command.server->channels.size(); i++)
	{
		std::cout << "name:" << command.server->channels[i].getName() << std::endl;
		std::cout << "key:" << command.server->channels[i].getKey() << std::endl;
	} */
	//	buffer = ERR_INVITEONLYCHAN(client.getNickname(), message[1]); lista ccon usuarios invitados. comprobar y meter.
}

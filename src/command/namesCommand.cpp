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
			if (i + 1 == raw.size())
				return raw.substr(0, i);
		if (raw[i] == ',')
				if (std::isspace(raw[i + 1]))
					return raw.substr(0, i);
		if (raw[i] == ',')
				if (raw[i + 1] != '#' && raw[i + 1] != '&')
					return raw.substr(0, i);
	}
	return raw;
}

static void	lexerNames(std::vector<std::string>& channelNames, std::string raw)
{
	std::string processed;

	processed = processRaw(raw);
	channelNames = splitString(processed, ',');
}


# define RD(client) (":" + client + ":" "\r\n")


static void printNames(Client& client, std::string& result)
{
	std::string str = RD(result);
	
	(void) client;
	//send(client.getSocket(), str.c_str(), str.size(), 0);
}


static void showName(Command& command, std::string& channelName, std::string& buffer)
{
	Server&						server = *command.server;
	std::vector<Channel>&		channel = server.channels;
	Client&						client = *command.client;

(void) buffer;
	std::string result;

	for (size_t i = 0; i != channel.size(); i++)
	{
		if (isEqualStr(channel[i].getName(), channelName))
		{
			result = channel[i].getOnlineUsersList();
			printNames(client, result);

	
		}
	}

}

void namesCommand(Command& command)
{
	std::string&				buffer = *command.buffer;

	std::vector<std::string>	channelNames;

	lexerNames(channelNames, command.raw);

	std::vector<std::string>::iterator it = channelNames.begin();
	while (it != channelNames.end())
	{
		std::cout << "namee: " << *it << std::endl;
		it++;	
	}
	for (size_t i = 0; i != channelNames.size(); i++)
	{
		showName(command, channelNames[i], buffer);
	}
	return ;
}
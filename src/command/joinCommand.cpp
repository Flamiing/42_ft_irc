/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/06 11:29:21 by guilmira         ###   ########.fr       */
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

/* _GUILLE faltaria parseo de asegurar que cada canal tiene su key */
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

void	lexerJoin(std::vector<std::string>& channelNames, std::vector<std::string>& keyNames, std::string raw)
{
	channelNames = getChannelNames(raw, JOIN);
	std::string lastElement = channelNames.back();
	std::string sub;
	size_t	lastPos = channelNames.size();

	size_t pos = raw.find_last_of(lastElement);
    if (pos != std::string::npos && raw.size() > pos + 1)
	{
        sub = raw.substr(pos + 1);
		keyNames = getChannelNames(sub, lastElement);
    }
	if (lastPos > keyNames.size())
		for (size_t i = 0; i < lastPos-keyNames.size(); i++)
			keyNames.push_back("");
}

/* _GUILLE ¿esta poniendo un hastag por defecto el cliente en mi nombre de canal? ¿O somos nosotros? */
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

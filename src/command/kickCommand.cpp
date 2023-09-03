/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:16 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/03 16:16:14 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

//KICK SIN MENSAJE PARA TODOS LOS USERS-> :worbam!~worbam@151.red-83-33-35.dynamicip.rima-tde.net KICK #prueba flamiing :flamiing
//KICK CON MENSAJE PARA TODOS LOS USERS -> :worbam!~worbam@151.red-83-33-35.dynamicip.rima-tde.net KICK #prueba flamiing :mensaje
//Te puedes autokickear y nadie tiene OP mas

static bool userNotInChannel(Server& server, std::string& nickname, std::string& channelName)
{
	std::vector<Channel> channels = server.getChannels();
	std::vector<Channel>::iterator it = channels.begin();
	std::string::size_type found;

	while (it != channels.end())
	{
		if ((*it).getName() == channelName)
		{
			found = ((*it).getOnlineUsersList()).find(nickname);
			if (found != std::string::npos)
				return false;
		}
		it++;
	}
	
	return true;
}

static std::string getKickReply(Client& client, Command& command)
{
	std::string reply;
	
	if (command.message.size() == 3
		|| (command.message.size() == 4 && command.message[3] == ":"))
		reply = RPL_KICKWITHNOMSG(client.getNickname(), client.getUsername(),
				command.message[1], command.message[2]);
	else
	{
		if (command.message[3][0] != ':')
		{
			command.message[3] = ":" + command.message[command.message.size() - 1];
			reply = RPL_KICKWITHMSG(client.getNickname(), client.getUsername(),
				command.message[1], command.message[2], command.message[3]);
		}
		else
		{
			std::vector<std::string> remove;
			remove.push_back(command.cmd);
			remove.push_back("#");
			remove.push_back(command.message[1]);
			remove.push_back(command.message[2]);
			std::string messageToSend = getMessage(command.raw, remove);
			reply = RPL_KICKWITHMSG(client.getNickname(), client.getUsername(),
				command.message[1], command.message[2], messageToSend);
		}
	}
	return reply;
}

static bool notInChannel(Client& client, std::string& channelName)
{
	std::vector<Channel> channels = client.getJoinedChannels();
	std::vector<Channel>::const_iterator it = channels.begin();

	while (it != channels.end())
	{
		if ((*it).getName() == channelName)
			return false;
		it++;
	}
	return true;
}

static bool handleErrors(Server& server, Client& client, std::string& buffer, Command& command)
{
	if (command.message.size() < 3 || (command.message.size() == 3 && command.message[2] == ":"))
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.cmd);
		return true;
	}
	else if (channelNotFound(server.getChannels(), command.message[1]))
	{
		buffer = ERR_NOSUCHCHANNEL(client.getNickname(), command.message[1]);
		return true;
	}
	else if (notInChannel(client, command.message[1]))
	{
		buffer = ERR_NOTONCHANNEL(client.getNickname(), command.message[1]);
		return true;
	}
	else if (userNotInChannel(server, command.message[2], command.message[1]))
	{
		buffer = ERR_NOSUCHNICK(client.getNickname(), command.message[2]);
		return true;
	}
	// TODO: Gestionar ERR_CHANOPRIVSNEEDED cuando el usuario
	// que ejecuta el comando no sea operador del canal
	return false;
}

void kickCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;
	
	if (handleErrors(server, client, buffer, command))
		return ;
	std::string reply = getKickReply(client, command);
	server.disconnectFromChannel(command.message[2], command.message[1], reply);
}
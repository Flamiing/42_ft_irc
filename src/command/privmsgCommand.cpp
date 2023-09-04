/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 15:14:18 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool handleErrors(Client& client, std::string& buffer, Command& command)
{
	if (command.message.size() == 1)
	{
		buffer = ERR_NORECIPIENT(client.getNickname(), command.cmd);
		return true;
	}
	else if (command.message.size() == 2)
	{
		buffer = ERR_NOTEXTTOSEND(client.getNickname());
		return true;
	}
	// TODO: Hay que gestionar ERR_CANNOTSENDTOCHAN, pero necesitamos que los modos esten hechos
	return false;
}

static void sendMessageToUser(Server& server, Client& client, const std::string& user, const std::string& messageToSend)
{
	std::string reply;
	
	if (!server.userInServer(user))
	{
		reply = ERR_NOSUCHNICK(client.getNickname(), user);
		send(client.getSocket(), reply.c_str(), reply.size(), 0);
		return ;
	}
	std::string rawNickname = server.getRawNickname(user);
	reply = RPL_PRIVMSG(client.getNickname(), client.getUsername(), rawNickname, messageToSend);
	int recipientSocket = server.getSocketByNickname(rawNickname);
	send(recipientSocket, reply.c_str(), reply.size(), 0);
}

static void sendMessageToChannel(Server& server, Client& client, const std::string& channel, const std::string& messageToSend)
{
	std::vector<Channel> channels = client.getJoinedChannels();
	std::vector<Channel>::iterator it = channels.begin();
	bool messageSended = false;
	std::string reply;
	
	while (it != channels.end())
	{
		if (toUpperCase((*it).getName()) == toUpperCase(channel))
		{
			reply = RPL_PRIVMSG(client.getNickname(), client.getUsername(), (*it).getName(), messageToSend);
			(*it).messageOnlineUsers(client.getNickname(), reply);
			messageSended = true;
			break ;
		}
		it++;
	}
	if (!messageSended)
	{
		if (channelNotFound(server.getChannels(), channel))
			reply = ERR_NOSUCHCHANNEL(client.getNickname(), channel);
		else
			reply = ERR_NOTONCHANNEL(client.getNickname(), channel);
		send(client.getSocket(), reply.c_str(), reply.size(), 0);
	}
}

static void sendMessageToReceivers(Server& server, Client& client, std::vector<std::string>& receivers, std::string& messageToSend)
{
	std::vector<std::string>::iterator it = receivers.begin();

	while (it != receivers.end())
	{
		if ((*it)[0] == '#' || (*it)[0] == '&')
			sendMessageToChannel(server, client, *it, messageToSend);
		else
			sendMessageToUser(server, client, *it, messageToSend);
		it++;
	}
}

void privmsgCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(client, buffer, command))
		return ;
	std::string messageToSend = getMessageToSend(command, 2);
	std::vector<std::string> receivers = splitString(command.message[1], ',');
	sendMessageToReceivers(server, client, receivers, messageToSend);
}
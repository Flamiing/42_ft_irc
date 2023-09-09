/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 02:45:13 by alaaouam         ###   ########.fr       */
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
	else if (command.message.size() == 2 || (command.message.size() == 3
				&& command.message[2].size() == 1 && command.message[2] == ":"))
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
	Client awayClient = server.getClientByNickname(user);
	if (awayClient.isAway)
	{
		reply = RPL_AWAY(client.getNickname(), awayClient.getNickname(), awayClient.awayMessage);
		send(client.getSocket(), reply.c_str(), reply.size(), 0);
	}
}

static void sendMessageToChannel(Server& server, Client& client, std::string& channel, const std::string& messageToSend)
{
	std::vector<Channel> channels = server.channels;
	std::vector<Channel>::iterator it = channels.begin();
	std::string reply;
	
	while (it != channels.end())
	{
		if (toUpperCase((*it).getName()) == toUpperCase(channel)
			&& (!userNotInChannel(server, client.getNickname(), channel)
			|| (*it).modes['n'] != true))
		{
			if (!server.isBanned(client, channel) && (!(*it).modes['m']
				|| ((*it).modes['m'] && (*it).userCanTalk(client.getNickname()))))
			{
				reply = RPL_PRIVMSG(client.getNickname(), client.getUsername(), (*it).getName(), messageToSend);
				(*it).messageOnlineUsers(client.getNickname(), reply);
			}
			else
			{
				reply = ERR_CANNOTSENDTOCHAN(client.getNickname(), (*it).getName());
				send(client.getSocket(), reply.c_str(), reply.size(), 0);
			}
			return ;
		}
		it++;
	}
	if (channelNotFound(server.channels, channel))
		reply = ERR_NOSUCHCHANNEL(client.getNickname(), channel);
	else
		reply = ERR_NOTONCHANNEL(client.getNickname(), channel);
	send(client.getSocket(), reply.c_str(), reply.size(), 0);
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
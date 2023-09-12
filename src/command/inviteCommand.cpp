/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 18:34:08 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"


static bool parserInvite(Command& command)
{
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;


	if (static_cast<int>(command.message.size()) < 3) /* _GUILLE undernet revisar si deberia ser 3 */
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.message[0]);
		return true;
	}
	return false;

}


bool clientAlreadyConnected(std::string& channel, Client& client);

static void inviteToChannel(Command& command, std::string& guestName, std::string& channelName, Client& clientGuest)
{
	Server&						server = *command.server;
	std::string&				buffer = *command.buffer;
	Client&						client = *command.client;
	std::vector<Channel>&		channel = server.channels;

	std::string str;
	for (int i = 0; i < static_cast<int>(channel.size()); i++)
	{
		
		if (isEqualStr(channel[i].getName(), channelName))
		{
			if (!channel[i].checkOperator(client.getNickname()))
			{
				buffer = ERR_CHANOPRIVSNEEDED(client.getNickname(), channel[i].getName());
				return;
			}
			else if (!client.isConnectedToChannel(channel[i]))
			{
				buffer = ERR_NOTONCHANNEL(client.getNickname(), command.message[0]);
				return;
			}
			else
			{
				str = channel[i].getName();
				if (clientAlreadyConnected(str, clientGuest))
				{
					buffer = ERR_USERONCHANNEL(client.getNickname(), guestName, channel[i].getName());
					return ;
				}
				channel[i].addInvitedUser(guestName);
				return ;
			}
		}
	}
	buffer = ERR_NOSUCHCHANNEL(client.getNickname(), command.message[2]);
	return;
}

void inviteCommand(Command& command)
{

	Server&						server = *command.server;
	std::string&				buffer = *command.buffer;
	Client&						client = *command.client;


	std::map<int, Client> clientMap = server.getClients();
	std::map<int, Client>::iterator it = clientMap.begin();

	if (parserInvite(command))
		return ;
	while (it != clientMap.end())
	{
		if (isEqualStr(it->second.getNickname(), command.message[1]))
		{
			;
			if (command.message.size() > 2)
				inviteToChannel(command, command.message[1], command.message[2], it->second);
			return ;
		}
		it++;
	}
	buffer = ERR_NOSUCHNICK(client.getNickname(), command.message[1]);

}

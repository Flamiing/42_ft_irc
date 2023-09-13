/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:35:00 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/13 12:27:10 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void static changeTopic(Client& client, std::vector<std::string> message, Channel& channel, std::string& buffer)
{
 	if (channel.checkOperator(client.getNickname()))
		channel.setTopic(message[2]);
	else
		buffer = ERR_CHANOPRIVSNEEDED(client.getNickname(), channel.getName());
}

static void viewTopic(Client& client, Channel& channel, std::string& buffer)
{
	if (!channel.getTopic().empty())
		buffer = RPL_TOPIC(client.getNickname(), channel.getName(), channel.getTopic());
	else
		buffer = RPL_NOTOPIC(client.getNickname(), channel.getName());
}	

static bool parserTopic(Command& command)
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

/* _GUILLE cerciorarse de que no hay channels con el mismo nombre */
void topicCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;
	std::vector<Channel>&		channel = server.channels;

	if (parserTopic(command))
		return ;
	for (int i = 0; i < static_cast<int>(channel.size()); i++)
	{
		if (isEqualStr(channel[i].getName(), command.message[1]))
		{
			if (!client.isConnectedToChannel(channel[i]))
			{
				buffer = ERR_NOTONCHANNEL(client.getNickname(), command.message[0]);
				return ;
			}
			if (command.message.size() == 2)
				viewTopic(client, channel[i], buffer);
			else
				changeTopic(client, command.message, channel[i], buffer);
			return ;
		}
	}
	buffer = ERR_NOSUCHCHANNEL(client.getNickname(), command.message[1]);
	return ;
}
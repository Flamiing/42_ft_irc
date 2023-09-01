/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:35:00 by guilmira          #+#    #+#             */
/*   Updated: 2023/09/01 15:10:03 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
   Command: TOPIC
   Parameters: <channel> [<topic>]

   The TOPIC message is used to change or view the topic of a channel.
   The topic for channel <channel> is returned if there is no <topic>
   given.  If the <topic> parameter is present, the topic for that
   channel will be changed, if the channel modes permit this action. */

#include "../../inc/Server.hpp"

std::string displayMsg(std::string number, std::string str, std::string clientNick)
{
	return (std::string(":localhost " + number + " " + clientNick + str + "\r\n") );
}

void static changeTopic(Client& client, std::vector<std::string> message, Channel& channel, std::string& buffer)
{
	std::string const mode	= channel.getMode();

	if (!mode.compare("+t"))
	{
		(void) message;
		return ;
		/* _GUILEL set topic name */
	}
	else
		buffer = ERR_INVITEONLYCHAN(client.getNickname(), channel.getName());
		

}

static void viewTopic(Client& client, Channel& channel, std::string& buffer)
{
	if (!channel.getTopic().empty())
		buffer = RPL_TOPIC(client.getNickname(), channel.getName(), channel.getTopic());
	else
		buffer = RPL_NOTOPIC(client.getNickname(), channel.getName());
}

static bool isCommandcorrect(std::vector<std::string> message, int lenght)
{
	if (static_cast<int>(message.size()) > lenght)
		return (false);
	else
		return (true);
}

/* _GUILLE cerciorarse de que no hay channels con el mismo nombre */
void topicCommand(Command& command)
{

	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;
	std::vector<Channel> const&		channel = command.server->getChannels();
(void) server;
	if (!isCommandcorrect(command.message, 3))
	{
		displayMsg("666", "too many parameters", client.getNickname());
		return ;
	}
	for (int i = 0; i < static_cast<int>(channel.size()); i++)
	{
		if (!channel[i].getName().compare(command.message[1]))
		{
			return ;
			/* if (command.message.size() == 2)
				viewTopic(client, channel[i], buffer);
			else
				changeTopic(client, command.message, channel[i], buffer); */
		}
		else	
		{
			buffer = displayMsg("666", "Channel does not exist", client.getNickname());
			return ;
		}
	}
	

	
	
}
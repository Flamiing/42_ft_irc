/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:52:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/25 19:42:43 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/commands.hpp"
# include "../../inc/Channel.hpp"
# include "../../inc/Server.hpp"

static bool channelNotFound(std::vector<Channel>& channels, std::string channelToFind)
{
	std::vector<Channel>::const_iterator it = channels.begin();
	
	while (it != channels.end())
	{
		if ((*it).getName() == channelToFind)
			return false;
		it++;
	}
	return true;
}

static void joinChannel(Server& server, std::vector<Channel> channels, Client& client, std::vector<std::string>& message)
{
	if (channels.size() == 0 || channelNotFound(channels, message[1]))
		server.addChannel(message[1]);
	if (message.size() == 2)
		server.connectToChannel(message[1], client, "");
	else
		server.connectToChannel(message[1], client, message[2]);
}

/* static bool handleErrors(std::string& buffer, std::vector<std::string>& message)
{
	if 
} */

void joinCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
	/* if (handleErrors(buffer, message))
		return ; */
	message[1].erase(0, 1);
	joinChannel(server, server.getChannels(), client, message);
	(void)buffer;
}
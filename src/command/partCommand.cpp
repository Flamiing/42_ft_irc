/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:55:48 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 22:41:17 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static void partFromChannels(Server& server, Client& client, std::vector<std::string>& channels)
{
	std::vector<std::string>::iterator channel = channels.begin();
	
	while (channel != channels.end())
	{
		server.partFromChannel(client, *channel);
		channel++;
	}
}

void partCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;
	std::vector<std::string> channels = getChannelNames(command.raw);

	if (command.message.size() < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.cmd);
		return ;
	}
	else if (!findChannels(client, server.channels, channels))
		return ;
	partFromChannels(server, client, channels);
}
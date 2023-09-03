/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:55:48 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/03 22:59:29 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool handleErrors(Server& server, Client& client, std::string& buffer, Command& command)
{
	if (command.message.size() < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.cmd)
		return true;
	}
	else if (channelNotFound(server.getChannels(), command.message[1]))
	{
		buffer = ERR_NOSUCHCHANNEL(client.getNickname(), command.message[1]);
		return true;
	}
}

void partCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(server, client, buffer, command.message))
}
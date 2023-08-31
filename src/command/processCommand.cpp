/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 13:13:53 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/commands.hpp"

#include "../../inc/Command.hpp"

void processCommand(Server& server, Client& client, std::string& buffer, Command& command)
{

	std::map<std::string, customFunctionType>& 				mapCommand = server.mapCommand;
	std::map<std::string, customFunctionType>::iterator		it;
	
	it = mapCommand.find(buffer);
	if (!command.cmd.compare(PASS))
		mapCommand[PASS](command);
	else if (client.getPassAuth() == true && !command.cmd.compare(USER))
		mapCommand[USER](command);
	else if (client.getPassAuth() == true && !command.cmd.compare(NICK))
		mapCommand[NICK](command);
	else if (!command.cmd.compare(PONG))
		return ;
	else if (client.getAuth() == true)
	{
		if (it != mapCommand.end())
			mapCommand[command.cmd](command);
		else
			buffer = ERR_UNKNOWNCOMMAND(client.getNickname(), command.cmd);
	}
	else
	{
		if (client.getAuth() == true)
			buffer = ERR_NOTREGISTERED(client.getNickname());
		else
			buffer = ERR_NOTREGISTERED(client.getWrongNickname());
	}
}
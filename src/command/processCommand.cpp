/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 14:35:23 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void processCommand(Command& command)
{

	std::map<std::string, customFunctionType>& 				mapCommand = command.server->mapCommand;
	std::map<std::string, customFunctionType>::iterator		it;
	
	it = mapCommand.find(*command.buffer);
	if (!command.cmd.compare(PASS))
		mapCommand[PASS](command);
	else if (command.client->getPassAuth() == true && !command.cmd.compare(USER))
		mapCommand[USER](command);
	else if (command.client->getPassAuth() == true && !command.cmd.compare(NICK))
		mapCommand[NICK](command);
	else if (!command.cmd.compare(PONG))
		return ;
	else if (command.client->getAuth() == true)
	{
		if (it != mapCommand.end())
			mapCommand[command.cmd](command);
		else
			*command.buffer = ERR_UNKNOWNCOMMAND(command.client->getNickname(), command.cmd);
	}
	else
	{
		if (command.client->getAuth() == true)
			*command.buffer = ERR_NOTREGISTERED(command.client->getNickname());
		else
			*command.buffer = ERR_NOTREGISTERED(command.client->getWrongNickname());
	}
}
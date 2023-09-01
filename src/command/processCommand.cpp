/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 05:08:48 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static void processGeneralCommands(Command& command, std::map<std::string, customFunctionType>& mapCommand)
{
	std::map<std::string, customFunctionType>::iterator		it;
	
	it = mapCommand.find(command.cmd);
	if (command.client->getAuth() == true)
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

void processCommand(Command& command)
{

	std::map<std::string, customFunctionType>& 				mapCommand = command.server->mapCommand;
	
	if (command.cmd.compare(PASS) == 0)
		mapCommand[PASS](command);
	else if (command.client->getPassAuth() == true && command.cmd.compare(USER) == 0)
		mapCommand[USER](command);
	else if (command.client->getPassAuth() == true && command.cmd.compare(NICK) == 0)
		mapCommand[NICK](command);
	else if (command.cmd.compare(PONG) == 0)
		return ;
	else
		processGeneralCommands(command, mapCommand);
}
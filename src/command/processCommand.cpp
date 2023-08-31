/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:10:01 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 12:53:09 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"
#include "../../inc/commands.hpp"

#include "../../inc/Command.hpp"

//_GUILLE metodo de server
void fillMap(std::map<std::string, customFunctionType>& mapCommand)
{
	mapCommand[PASS] = &passCommand;
	mapCommand[USER] = &userCommand;
	mapCommand[NICK] = &nickCommand;
	mapCommand[JOIN] = &joinCommand;
	//mapCommand[QUIT] = &quitCommand;
	//mapCommand[PRIVMSG] = &privmsgCommand;
}

void processCommand(Client& client, std::string& buffer, Command& command)
{

	std::map<std::string, customFunctionType> 				mapCommand;
	std::map<std::string, customFunctionType>::iterator		it;
	
	fillMap(mapCommand);
	it = mapCommand.find(buffer);
	if (!command.cmd.compare(PASS))
		mapCommand[PASS](command);
	else if (client.getPassAuth() == true && !command.cmd.compare(USER))
		mapCommand[USER](command);
	else if (client.getPassAuth() == true && !command.cmd.compare(NICK))
		mapCommand[NICK](command);
	else if (!command.cmd.compare(PONG))
		return ;
	else if (client.getAuth() == true && it != mapCommand.end())
		mapCommand[command.cmd](command);
	else
	{
		if (client.getAuth() == true)
			buffer = ERR_NOTREGISTERED(client.getNickname());
		else
			buffer = ERR_NOTREGISTERED(client.getWrongNickname());
	}
}
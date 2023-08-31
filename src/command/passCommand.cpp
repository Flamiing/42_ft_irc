/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:35:46 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 12:35:09 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"
//_GUILLE homogeneizar includes

void passCommand(Command& command)
{
	if (command.client->getAuth() == true)
	{
		*command.buffer = ERR_ALREADYREGISTRED(command.client->getNickname());
		return ;
	}
	else if (command.message.size() < 2)
	{
		*command.buffer = ERR_NEEDMOREPARAMS(command.client->getNickname(), command.message[0]);
		return ;
	}
	else if (command.server->getPassword() == command.message[1])
		command.client->setPassAuth(true);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:35:46 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 16:02:10 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void passCommand(Command& command)
{
	Client&						client = *command.client;

	if (client.getAuth() == true)
	{
		*command.buffer = ERR_ALREADYREGISTRED(client.getNickname());
		return ;
	}
	else if (command.message.size() < 2)
	{
		*command.buffer = ERR_NEEDMOREPARAMS(client.getNickname(), command.message[0]);
		return ;
	}
	else if (command.server->getPassword() == command.message[1])
		client.setPassAuth(true);
}
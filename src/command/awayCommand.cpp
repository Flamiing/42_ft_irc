/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awayCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 02:52:41 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 03:39:43 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void awayCommand(Command& command)
{
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;
	
	if (command.message.size() == 1)
	{
		buffer = RPL_UNAWAY(client.getNickname());
		client.awayMessage = "";
		client.isAway = false;
	}
	else
	{
		if (!client.isAway)
		{
			client.awayMessage = getMessageToSend(command, 1);
			client.isAway = true;
		}
		buffer = RPL_NOWAWAY(client.getNickname());
	}
}
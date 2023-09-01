/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dieCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 03:14:59 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 03:33:23 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void dieCommand(Command& command)
{
	Server&						server = *command.server;
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (!client.isOperator())
	{
		buffer = ERR_NOPRIVILEGES(client.getNickname());
		return ;
	}
	server.closeAllSockets();
	exit(0);
}
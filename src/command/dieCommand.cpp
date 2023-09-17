/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dieCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 03:14:59 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/17 03:45:25 by alaaouam         ###   ########.fr       */
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
	std::cout << SERVER << BOLD_YELLOW << SERVER_SHUT_DOWN;
	exit(0);
}
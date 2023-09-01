/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 02:35:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 03:09:33 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool handleErrors(Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (message.size() < 3)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), message[0]);
		return true;
	}
	else if (message[1].compare(OPERATOR_NAME) != 0)
	{
		buffer = ERR_NOOPERHOST(client.getNickname());
		return true;
	}
	else if (message[2].compare(OPERATOR_PASS) != 0)
	{
		buffer = ERR_PASSWDMISMATCH(client.getNickname());
		return true;
	}
	return false;
}

void operCommand(Command& command)
{
	Client&						client = *command.client;
	std::string&				buffer = *command.buffer;

	if (handleErrors(client, buffer, command.message))
		return ;
	client.setAsOperator();
	buffer = RPL_YOUREOPER(client.getNickname());
}
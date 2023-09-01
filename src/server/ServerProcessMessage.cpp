/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerProcessMessage.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:09:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 03:49:12 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_processMessage(const int& client, std::string message)
{
	std::string buffer;
	if (message[message.size() - 1] == '\n')
		message.erase(message.size() - 1);
	if (message[message.size() - 1] == '\r')
		message.erase(message.size() - 1);
	Command		command(this, &this->_clients[client], &buffer, message);
	if (this->_clients[client].getPassAuth() == false && command.cmd != PASS)
		buffer = ERR_NOTREGISTERED(this->_clients[client].getNickname());
	else
		processCommand(command);
	send(this->_clients[client].getSocket(), buffer.c_str(), buffer.size(), 0);
	buffer = "";
}
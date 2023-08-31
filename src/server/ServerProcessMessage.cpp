/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerProcessMessage.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:09:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 12:42:30 by guilmira         ###   ########.fr       */
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
	IRCMessage messageIRC(message);
	Command		command(this, &this->_clients[client], &buffer, message);
	//_GUILLE falta elminar clase message cuando hagamos MERGE
	if (this->_clients[client].getPassAuth() == false && messageIRC.cmd != PASS)
		buffer = ERR_NOTREGISTERED(this->_clients[client].getNickname());
	else
		processCommand(this->_clients[client], buffer, command);
	send(this->_clients[client].getSocket(), buffer.c_str(), buffer.size(), 0);
	buffer = "";
}
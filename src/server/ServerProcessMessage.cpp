/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerProcessMessage.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:09:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/28 22:01:12 by alaaouam         ###   ########.fr       */
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
	
	if (this->_clients[client].getPassAuth() == false && messageIRC.cmd != PASS)
		buffer = ERR_NOTREGISTERED(this->_clients[client].getNickname());
	else
		processCommand(*this, this->_clients[client], buffer, messageIRC);
	send(this->_clients[client].getSocket(), buffer.c_str(), buffer.size(), 0);
	buffer = "";
}
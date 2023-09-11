/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerProcessMessage.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:09:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 08:23:26 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool Server::_processMessage(const int& client, std::string message)
{
	std::string buffer;
	int keyToFind = client;
	if (message[message.size() - 1] == '\n') /* _GUILLE bastaria con una linea aqui para bloquear que nc funcione sin el -c */
		message.erase(message.size() - 1);
	if (message[message.size() - 1] == '\r')
		message.erase(message.size() - 1);
	Command		command(this, &this->_clients[client], &buffer, message);
	if (this->_clients[client].getPassAuth() == false && command.cmd != PASS)
	{
		std::cout << command.cmd;
		buffer = ERR_NOTREGISTERED(this->_clients[client].getNickname());
	}
	else
		processCommand(command);
	std::map<int, Client>::iterator found = this->_clients.find(keyToFind);
	if (found != this->_clients.end())
		send(this->_clients[client].getSocket(), buffer.c_str(), buffer.size(), MSG_NOSIGNAL);
	buffer = "";
	if (command.cmd == QUIT)
		return false;
	return true;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerProcessMessage.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:09:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/16 20:07:45 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool onlySpaces(const std::string& str)
{
	size_t pos = 0;
	while (pos < str.size())
	{
		if (str[pos] != ' ')
			return false;
		pos++;
	}
	return true;
}

bool Server::_processMessage(const int& client, std::string message)
{
	std::string buffer;
	int keyToFind = client;
	if (!message.empty() && message[message.size() - 1] == '\n')
		message.erase(message.size() - 1);
	if (!message.empty() && message[message.size() - 1] == '\r')
		message.erase(message.size() - 1);
	if (message.empty() || onlySpaces(message))
		return true;
	std::cout << SERVER << BOLD_CYAN << CLIENT_MESSAGE_RECIVED(numberToString(client), message) << RESET;
	Command		command(this, &this->_clients[client], &buffer, message);
	if (this->_clients[client].getPassAuth() == false && command.cmd != PASS)
		buffer = ERR_NOTREGISTERED(this->_clients[client].getNickname());
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
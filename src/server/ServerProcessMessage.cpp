/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerProcessMessage.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:09:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/24 15:18:08 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_processMessage(const int& client, char* message)
{
	std::string buffer;
	std::string messageStr = message;
	if (messageStr[messageStr.size() - 1] == '\n')
		messageStr.erase(messageStr.size() - 1);
	if (messageStr[messageStr.size() - 1] == '\r')
		messageStr.erase(messageStr.size() - 1);
	std::vector<std::string> messageVector = splitString(messageStr, ' ');
	
	if (this->_clients[client].getPassAuth() == false && messageVector[0] != PASS)
		buffer = ERR_NOTREGISTERED(this->_clients[client].getNickname());
	else
		processCommand(*this, this->_clients[client], buffer, messageVector);
	send(this->_clients[client].getSocket(), buffer.c_str(), buffer.size(), 0);
	buffer = "";
}
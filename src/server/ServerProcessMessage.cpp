/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerProcessMessage.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:09:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/23 16:17:29 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_processMessage(const int& client, char* data)
{
	std::string buffer;
	std::string dataStr = data;
	if (!dataStr.empty() && dataStr[dataStr.size() - 1] == '\n')
    	dataStr.erase(dataStr.size() - 1);
	std::vector<std::string> dataVector = splitString(dataStr, ' ');
	
	if (this->_clients[client].getPassAuth() == false && dataVector[0] != PASS)
		buffer = NO_PASS;
	else if (this->_clients[client].getPassAuth() == false && dataVector[0] == PASS)
		passCommand(*this, this->_clients[client], buffer, dataVector);
	else if (dataVector[0] != PASS)
		processCommand(this->_clients[client], buffer, dataVector);
	send(this->_clients[client].getSocket(), buffer.c_str(), buffer.size(), 0);
	buffer = "";
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClientDisconnection.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:02:51 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 23:27:15 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

size_t Server::getPollinPosition(Client& client)
{
	size_t pos = 0;

	while(pos < this->_pollFds.size())
	{
		if (this->_pollFds[pos].fd == client.getSocket())
			return pos;
		pos++;
	}
	return 0;
}

void Server::disconnect(size_t client)
{
	std::cout << "Client at socket #" << this->_pollFds[client].fd << " disconnected." << std::endl;
	this->_clients[_pollFds[client].fd].buffer = "";
	this->_clients.erase(this->_pollFds[client].fd);
	close(this->_pollFds[client].fd);
	this->_pollFds.erase(this->_pollFds.begin() + client);
	client--;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClientDisconnection.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:02:51 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 05:31:37 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::disconnect(size_t& client)
{
	std::cout << "Client at socket #" << this->_pollFds[client].fd << " disconnected." << std::endl;
	this->_clients[_pollFds[client].fd].buffer = "";
	this->_clients.erase(this->_pollFds[client].fd);
	close(this->_pollFds[client].fd);
	this->_pollFds.erase(this->_pollFds.begin() + client);
	client--;
}
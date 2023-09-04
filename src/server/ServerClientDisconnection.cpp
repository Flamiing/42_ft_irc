/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClientDisconnection.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:02:51 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 00:54:44 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::disconnect(size_t& client)
{
	std::cout << SERVER << BOLD_YELLOW << CLIENT_DISCONNECTED(numberToString(this->_pollFds[client].fd)) << RESET;
	this->_clients[_pollFds[client].fd].buffer = "";
	this->_clients.erase(this->_pollFds[client].fd);
	close(this->_pollFds[client].fd);
	this->_pollFds.erase(this->_pollFds.begin() + client);
	client--;
}
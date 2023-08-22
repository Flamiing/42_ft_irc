/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerRun.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:03:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 17:53:06 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_setupSever(void)
{
	this->_socket = INVALID_SOCKET;
	this->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_socket == INVALID_SOCKET)
	{
		printError(ERROR_SOCKET, W_ERRNO);
		exit(1);
	}
	
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(this->getPort());
	this->_address.sin_addr.s_addr = inet_addr(LOCALHOST);
}

void Server::runServer(void)
{
	int reuse = 1;
	
	_setupSever();
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == ERROR)
	{
		printError(ERROR_SETSOCKOPT, W_ERRNO);
		exit(1);
	}
	if (bind(this->_socket, (struct sockaddr*)&this->_address,
		sizeof(this->_address)) == SOCKET_ERROR)
	{
		printError(ERROR_BIND, W_ERRNO);
		exit(1);
	}
	if (listen(this->_socket, MAX_CLIENTS) == SOCKET_ERROR)
	{
		printError(ERROR_LISTEN, W_ERRNO);
		exit(1);
	}
	std::cout << "IRC Server listening on port " << this->getPort() << "..." << std::endl;
	_handleClientConnections();
	close(this->_socket);
}
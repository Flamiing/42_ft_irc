/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerRun.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:03:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 15:02:12 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::initMapCommand(void)
{
	mapCommand[PASS] = &passCommand;
	mapCommand[USER] = &userCommand;
	mapCommand[NICK] = &nickCommand;
	mapCommand[JOIN] = &joinCommand;
	mapCommand[QUIT] = &quitCommand;
	mapCommand[NOTICE] = &noticeCommand;
	mapCommand[OPER] = &operCommand;
	mapCommand[DIE] = &dieCommand;
	mapCommand[KICK] = &kickCommand;
	mapCommand[PART] = &partCommand;
	mapCommand[PRIVMSG] = &privmsgCommand;
}

void Server::_setupSever(void)
{
	initMapCommand();
	this->_socket = INVALID_SOCKET;
	this->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_socket == INVALID_SOCKET)
	{
		printError(ERROR_SOCKET, W_ERRNO);
		exit(1);
	}
	
	this->_address.sin_family = AF_INET;
	this->_address.sin_port = htons(this->getPort());
	this->_address.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Server::closeAllSockets(void)
{
	size_t pos = 1;
	int fdToClose;
	
	while (pos < this->_pollFds.size())
	{
		fdToClose = this->_pollFds[pos].fd;
		this->_pollFds[pos].fd = -1;
		close(this->_clients[fdToClose].getSocket());
		pos++;
	}
	fdToClose = this->_pollFds[0].fd;
	this->_pollFds[0].fd = -1;
	close(this->_socket);
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
	std::cout << SERVER_LISTENING(numberToString(this->getPort()));
	_handleClientConnections();
	close(this->_socket);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClientConnections.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:10:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 23:46:26 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_newClient(int& clientSocket)
{
	struct pollfd clientPoll;
	
	clientPoll.fd = clientSocket;
	clientPoll.events = POLLIN;
	clientPoll.revents = 0;
	this->_clients[clientSocket] = Client(clientSocket);
	std::cout << "New client connected at socket #" << clientSocket << std::endl;
	this->_pollFds.push_back(clientPoll);
}

void Server::_handleClientRequest(size_t& client)
{
	char buffer[512] = {0};
	std::string& stash = this->_clients[_pollFds[client].fd].buffer;
	ssize_t bytesRead = recv(this->_pollFds[client].fd, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0)
	{
		stash = RPL_QUITWITHEOF(this->_clients[_pollFds[client].fd].getNickname(),
				this->_clients[_pollFds[client].fd].getUsername());
		this->disconnectClientFromChannels(this->_clients[_pollFds[client].fd].getNickname(), stash);
		disconnect(client);
	}
	else
	{
		std::string checkEOF(buffer);
		stash += checkEOF;
		if (checkEOF[checkEOF.size() - 1] != '\n')
			return ;
		std::cout << "Client at socket #" << this->_pollFds[client].fd << ": " << stash;
		_processMessage(this->_pollFds[client].fd, stash);
	}
	stash = "";
}

void Server::_handleClients(void)
{
	int clientSocket;
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
	
	for (size_t pos = 0; pos < this->_pollFds.size(); pos++)
	{
		if (this->_pollFds[pos].revents & POLLIN)
		{
			if (this->_pollFds[pos].fd == this->_socket)
			{
				clientSocket = accept(this->_socket, (struct sockaddr*)&clientAddr, &addrLen);
				if (clientSocket == ERROR)
					printError(ERROR_ACCEPT, W_ERRNO);
				else
					_newClient(clientSocket);
			}
			else
				_handleClientRequest(pos);
		}
	}
}

void Server::_handleClientConnections(void)
{
	int pollResult;
	struct pollfd serverPoll;
	
	serverPoll.fd = this->_socket;
	serverPoll.events = POLLIN;
	serverPoll.revents = 0;
	this->_pollFds.push_back(serverPoll);
	while (true)
	{
		pollResult = poll(this->_pollFds.data(), this->_pollFds.size(), -1);
		if (pollResult == POLL_FAILED)
		{
			printError(ERROR_POLL, W_ERRNO);
			close(this->_socket);
			exit(1);
		}
		_handleClients();
	}
}
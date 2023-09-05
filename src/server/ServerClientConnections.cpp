/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerClientConnections.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:10:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 04:05:35 by alaaouam         ###   ########.fr       */
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
	
	std::cout << SERVER << BOLD_GREEN << CLIENT_CONNECTION(numberToString(clientSocket)) << RESET;
	this->_pollFds.push_back(clientPoll);
}

void Server::_processBuffer(size_t& client, std::string& buffer)
{
	std::string bufferToProcess;
	std::string::size_type pos = buffer.find("\n");
	
	while (pos != std::string::npos)
	{
		if (buffer[0] == 0)
			buffer.erase(0, 1);
		if (buffer[0] == '\n')
			buffer.erase(0, 1);
		bufferToProcess = buffer.substr(0, pos);
		std::cout << SERVER << BOLD_CYAN << CLIENT_MESSAGE_RECIVED(numberToString(this->_pollFds[client].fd), bufferToProcess) << RESET;
		if (!_processMessage(this->_pollFds[client].fd, bufferToProcess))
			return ;
		buffer.erase(0, pos + 1);
		pos = buffer.find("\n");
	}
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
		_processBuffer(client, stash);
	}
	stash = "";
}

void Server::_handleClients(void)
{
	int clientSocket;
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
	
	for (this->pollSize = 0; this->pollSize < this->_pollFds.size(); this->pollSize++)
	{
		if (this->_pollFds[this->pollSize].revents & POLLIN)
		{
			if (this->_pollFds[this->pollSize].fd == this->_socket)
			{
				clientSocket = accept(this->_socket, (struct sockaddr*)&clientAddr, &addrLen);
				if (clientSocket == ERROR)
					printError(ERROR_ACCEPT, W_ERRNO);
				else
					_newClient(clientSocket);
			}
			else
				_handleClientRequest(this->pollSize);
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
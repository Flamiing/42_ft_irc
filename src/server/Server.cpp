/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 03:21:41 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Server.hpp"

/* CONSTRUCTORS /// DESTRUCTOR /// OPERATOR */
Server::Server(void) {}

Server::Server(const int port, const std::string& password) :  pollSize(0), _port(port), _password(password) {}

Server::Server(const Server& other) { (void)other; }

Server::~Server(void) {}

Server& Server::operator=(const Server& other) { (void)other; return *this; }


/* GETTER METHODS */
int Server::getPort(void) const { return this->_port; }
std::string Server::getPassword(void) const { return this->_password; }
std::map<int, Client> Server::getClients(void) const { return this->_clients; }

int Server::getSocketByNickname(const std::string nickname) const
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(nickname))
			break ;
		it++;
	}
	return it->second.getSocket();
}

Client Server::getClientByNickname(const std::string nickname) const
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(nickname))
			break ;
		it++;
	}
	return it->second;
}

std::string Server::getRawNickname(const std::string& modifiedNickname)
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(modifiedNickname))
			return it->second.getNickname();
		it++;
	}
	return modifiedNickname;
}

bool Server::userInServer(const std::string& nickname)
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(nickname))
			return true;
		it++;
	}
	return false;
}

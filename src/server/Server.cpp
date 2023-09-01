/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 10:50:19 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Server.hpp"

/* CONSTRUCTORS /// DESTRUCTOR /// OPERATOR */
Server::Server(void) {}

Server::Server(const int port, const std::string& password) :  _port(port), _password(password) {}

Server::Server(const Server& other) { (void)other; }

Server::~Server(void) {}

Server& Server::operator=(const Server& other) { (void)other; return *this; }


/* GETTER METHODS */
int Server::getPort(void) const { return this->_port; }
std::string Server::getPassword(void) const { return this->_password; }
std::map<int, Client> Server::getClients(void) const { return this->_clients; }
//std::vector<Channel> Server::getChannels(void) const { return this->_channels; }

std::vector<Channel> Server::getChannels(void)
{
	return (this->_channels);
}

int Server::getSocketByNickname(const std::string nickname) const
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (it->second.getNickname() == nickname)
			break ;
		it++;
	}
	return it->second.getSocket();
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
	return it->second.getNickname();
}

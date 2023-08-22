/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/21 22:43:36 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Server.hpp"

/* CONSTRUCTORS /// DESTRUCTOR /// OPERATOR */
Server::Server(void) {}

Server::Server(const Server& other)
{
	(void)other; 
}

Server::~Server(void) {}

Server& Server::operator=(const Server& other)
{
	(void)other;
	return *this;
}

Server::Server(const int port, const std::string& password) :  _port(port), _password(password), _connectedClients(0)
{
	
}

/* GETTER METHODS */
const int getPort(void) const { return this->_port }
const std::string getPassword(void) const { return this->_password }

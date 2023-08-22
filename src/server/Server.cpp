/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 16:51:01 by alaaouam         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:59:16 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 21:57:25 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

Client::Client(void) {}

Client::Client(int socket) : _socket(socket), _passAuth(false), _userAuth(false), _auth(false), _isOperator(false) {}

Client::Client(const Client& other)
{
	*this = other;
}

Client::~Client(void) {}

Client& Client::operator=(const Client& other) 
{ 
	if (this != &other)
	{
		this->_nickname = other._nickname;
		this->_username = other._username;
		this->_fullName = other._fullName;
		this->_socket = other._socket;
		this->_auth = other._auth;
		this->_isOperator = other._isOperator;
	}
	return *this;
}

int Client::getSocket(void) const { return this->_socket; }
bool Client::getPassAuth(void) const { return this->_passAuth; }
bool Client::getUserAuth(void) const { return this->_userAuth; }
bool Client::getAuth(void) const { return this->_auth; }

void Client::setPassAuth(const bool auth)
{
	this->_passAuth = auth;
}

void Client::setUserAuth(const bool auth)
{
	this->_userAuth = auth;
	if (this->getPassAuth() == true && auth == true)
		this->_auth = auth;
}

void Client::setUsername(const std::string username)
{
	this->_username = username;
}

void Client::setNickname(const std::string nickname)
{
	this->_nickname = nickname;
}

void Client::setFullName(const std::string fullName)
{
	this->_fullName = fullName;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:59:16 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 12:30:15 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

Client::Client(void) {}

Client::Client(int socket, size_t pollFDPos) :
		buffer(), _socket(socket), _pollFDPos(pollFDPos) , _passAuth(false),
		_userAuth(false), _nickAuth(false), _auth(false), _isOperator(false) {}

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
		this->_pollFDPos = other._pollFDPos;
		this->_auth = other._auth;
		this->_passAuth = other._passAuth;
		this->_userAuth = other._userAuth;
		this->_nickAuth = other._nickAuth;
		this->_isOperator = other._isOperator;
		this->_joinedChannels = other._joinedChannels;

		/* std::vector<Channel>::const_iterator it = other._joinedChannels.begin();
		std::vector<Channel> newJoinedChannels;

		while (it != other._joinedChannels.end())
		{
			newJoinedChannels.push_back(*it);
			it++;
		}
		this->_joinedChannels = newJoinedChannels; */
	}
	return *this;
}

int Client::getSocket(void) const { return this->_socket; }
std::string Client::getUsername(void) const { return this->_username; }
std::string Client::getNickname(void) const { return this->_nickname; }
std::string Client::getWrongNickname(void) const { return this->_wrongNickname; }
bool Client::getPassAuth(void) const { return this->_passAuth; }
bool Client::getUserAuth(void) const { return this->_userAuth; }
bool Client::getNickAuth(void) const { return this->_nickAuth; }
bool Client::getAuth(void) const { return this->_auth; }
size_t Client::getPollFDPos(void) const { return this->_pollFDPos; }

void Client::setPassAuth(const bool auth)
{
	this->_passAuth = auth;
}

void Client::setNickAuth(const bool auth)
{
	this->_nickAuth = auth;
	if (this->getPassAuth() == true && this->getUserAuth() == true && auth == true)
		this->_auth = auth;
}

void Client::setUserAuth(const bool auth)
{
	this->_userAuth = auth;
	if (this->getPassAuth() == true && this->getNickAuth() == true && auth == true)
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

void Client::setWrongNickname(const std::string nickname)
{
	this->_wrongNickname = nickname;
}

void Client::setFullName(const std::string fullName)
{
	this->_fullName = fullName;
}

void Client::addToJoinedChannels(Channel& channel)
{
	this->_joinedChannels.push_back(channel);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:59:16 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/25 17:29:00 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

Client::Client(void) {}

Client::Client(int socket) :
		buffer(""), awayMessage(""), isAway(false), _nickname("*"), _socket(socket) , _passAuth(false),
		_userAuth(false), _nickAuth(false), _auth(false), _isOperator(false) {}

Client::Client(std::string& nickname) :
		buffer(""), awayMessage(""), isAway(false), _nickname(nickname), _passAuth(false),
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
		this->buffer = other.buffer;
		this->awayMessage = other.awayMessage;
		this->isAway = other.isAway;
		this->_nickname = other._nickname;
		this->_wrongNickname = other._wrongNickname;
		this->_username = other._username;
		this->_fullName = other._fullName;
		this->_socket = other._socket;
		this->_auth = other._auth;
		this->_passAuth = other._passAuth;
		this->_userAuth = other._userAuth;
		this->_nickAuth = other._nickAuth;
		this->_isOperator = other._isOperator;
		this->_joinedChannels = other._joinedChannels;
	}
	return *this;
}
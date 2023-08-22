/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:59:16 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 17:21:59 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

Client::Client(void) {}

Client::Client(int socket) : _socket(socket), _auth(false), _isOperator(false) {}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSetter.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:04:33 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 11:38:45 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

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
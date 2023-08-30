/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:18:27 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 19:05:23 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IRCMessage.hpp"

IRCMessage::IRCMessage(void) {}

IRCMessage::IRCMessage(const IRCMessage& other) { *this = other; }

IRCMessage::~IRCMessage(void) {}

IRCMessage& IRCMessage::operator=(const IRCMessage& other)
{
	if (this != &other)
	{
		this->raw = other.raw;
		this->cmd = other.cmd;
		
		size_t pos = 0;
		while (pos < other.vector.size())
		{
			this->vector.push_back(other.vector[pos]);
			pos++;
		}
	}
	return *this;
}

IRCMessage::IRCMessage(std::string& message)
{
	std::stringstream ss(message);
	std::string token;

	std::getline(ss, token, ' ');
	this->cmd = token;
	this->vector = splitString(message, ' ');
	this->raw = trimSpaces(message);
}
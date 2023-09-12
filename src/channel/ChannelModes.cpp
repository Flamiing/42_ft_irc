/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelModes.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 03:22:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/12 09:23:34 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Channel::_initChannelModes(void)
{
	this->modes[MODE_CHANNEL_OPERATOR] = false;
	this->modes[MODE_CHANNEL_PRIVATE] = false;
	this->modes[MODE_CHANNEL_SECRET] = false;
	this->modes[MODE_CHANNEL_INVITE_ONLY] = false;
	this->modes[MODE_CHANNEL_TOPIC_OPER_ONLY] = false;
	this->modes[MODE_CHANNEL_NO_MSG_FROM_OUTSIDE] = false;
	this->modes[MODE_CHANNEL_MODERATED] = false;
	this->modes[MODE_CHANNEL_USER_LIMIT] = false;
	this->modes[MODE_CHANNEL_BANNED] = false;
	this->modes[MODE_CHANNEL_SPEAK_ABILITY] = false;
	this->modes[MODE_CHANNEL_KEY] = false;
}

void Channel::_initModeFunctions(void)
{
	this->modesWithParams[MODE_CHANNEL_OPERATOR] = &Channel::setO;
	this->modesWithParams[MODE_CHANNEL_KEY] = &Channel::setK;
	this->modesWithParams[MODE_CHANNEL_USER_LIMIT] = &Channel::setL;
	this->modesWithParams[MODE_CHANNEL_BANNED] = &Channel::setB;
	this->modesWithParams[MODE_CHANNEL_SPEAK_ABILITY] = &Channel::setV;
	
	this->modesWithoutParams[MODE_CHANNEL_MODERATED] = &Channel::setM;
	this->modesWithoutParams[MODE_CHANNEL_INVITE_ONLY] = &Channel::setI;
	this->modesWithoutParams[MODE_CHANNEL_TOPIC_OPER_ONLY] = &Channel::setT;
	this->modesWithoutParams[MODE_CHANNEL_NO_MSG_FROM_OUTSIDE] = &Channel::setN;
	this->modesWithoutParams[MODE_CHANNEL_PRIVATE] = &Channel::setP;
	this->modesWithoutParams[MODE_CHANNEL_SECRET] = &Channel::setS;
}

bool Channel::checkOperator(std::string nickname)
{
	std::vector<std::string>::iterator it = this->_operators.begin();
	std::string reply;
	bool isOper = false;

	while (it != this->_operators.end())
	{
		if (toUpperCase(*it) == toUpperCase(nickname))
		{
			isOper = true;
			break ;
		}
		it++;	
	}
	return isOper;
}

static bool validMode(char c)
{
	size_t pos = 0;
	char validModes[] =
	{
		MODE_CHANNEL_PRIVATE, MODE_CHANNEL_SECRET,
		MODE_CHANNEL_INVITE_ONLY, MODE_CHANNEL_TOPIC_OPER_ONLY,
		MODE_CHANNEL_NO_MSG_FROM_OUTSIDE, MODE_CHANNEL_MODERATED
	};
	
	while (pos < 6)
	{
		if (c == validModes[pos])
			break ;
		pos++;
	}
	if (pos < 6)
		return true;
	return false;
}

void Channel::setMode(Client& client, char mode, std::string param, bool action)
{
	std::string reply;

	if (mode == '-' || mode == '+')
		return ;
	if (!checkOperator(client.getNickname()) && !client.isOperator())
	{
		reply = ERR_CHANOPRIVSNEEDED(client.getNickname(), this->getName());
		send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
		return ;
	}
	if (((this->modes[mode] == true && action == true)
		|| (this->modes[mode] == false && action == false))
		&& mode != 'o' && mode != 'b' && mode != 'l' && mode != 'k' && mode != 'v')
		return ;
	if (mode == 'o' || mode == 'k' || mode == 'l' || mode == 'b' || mode == 'v')
		(this->*modesWithParams[mode])(client, param, action);
	else if (validMode(mode))
		(this->*modesWithoutParams[mode])(client, action);
	else
	{
		reply = ERR_UNKNOWNMODE(client.getNickname(), mode);
		send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
	}
}
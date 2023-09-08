/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelModes.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 03:22:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 15:40:40 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool Channel::_checkOperator(std::string nickname)
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

void Channel::setMode(Client& client, char mode, std::string param, bool action)
{
	if (!_checkOperator(client.getNickname()) && !client.isOperator())
	{
		std::string reply = ERR_CHANOPRIVSNEEDED(client.getNickname(), this->getName());
		send(client.getSocket(), reply.c_str(), reply.size(), 0);
		return ;
	}
	if (((this->modes[mode] == true && action == true)
		|| (this->modes[mode] == false && action == false))
		&& mode != 'o' && mode != 'b' && mode != 'l' && mode == 'k' && mode != 'v')
		return ;
	if (mode == 'o' || mode == 'k' || mode == 'l' || mode == 'b' || mode == 'v')
		(this->*modesWithParams[mode])(client, param, action);
	else
		(this->*modesWithoutParams[mode])(client, action);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 01:00:27 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 01:46:18 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static void replyIfNotFound(Client& client, std::string& nickname)
{
	std::string reply = ERR_NOSUCHNICK(client.getNickname(), nickname);
	send(client.getSocket(), reply.c_str(), reply.size(), 0);
}

void Channel::_removeOperator(std::string& operatorToRemove)
{
	std::vector<std::string>::iterator it = this->_operators.begin();

	while (it != this->_operators.end())
	{
		if (toUpperCase(*it) == toUpperCase(operatorToRemove))
		{
			this->_operators.erase(it);
			break ;
		}
		it++;
	}
}

void Channel::setO(Client& client, std::string& param, bool action)
{
	std::string reply;
	std::vector<Client>::iterator it = this->_onlineUsers.begin();
	bool found = false;
	
	while (it != this->_onlineUsers.end())
	{
		if (toUpperCase(it->getNickname()) == toUpperCase(param))
		{
			this->modes[MODE_CHANNEL_OPERATOR] = true;
			if (action == MODE_CHANNEL_ADD && !_checkOperator(param))
			{
				this->_operators.push_back(param);
				reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+o", param);
				_informOnlineUsers(reply);
			}
			else if (action == MODE_CHANNEL_REMOVE)
			{
				_removeOperator(param);
				reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-o", param);
				_informOnlineUsers(reply);
			}
			return ;
		}
		it++;
	}
	if (!found)
		replyIfNotFound(client, param);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:44:37 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 16:26:40 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool Channel::userCanTalk(std::string nickname)
{
	std::vector<std::string>::iterator it = this->_canTalk.begin();
	
	if (_checkOperator(nickname))
		return true;
	while (it != this->_canTalk.end())
	{
		if (toUpperCase(*it) == toUpperCase(nickname))
			return true;
		it++;
	}
	return false;
}

void Channel::removeTalkingPermissions(std::string nickname)
{
	std::vector<std::string>::iterator it = this->_canTalk.begin();
	
	while (it != this->_canTalk.end())
	{
		if (toUpperCase(*it) == toUpperCase(nickname))
		{
			this->_canTalk.erase(it);
			return ;
		}
		it++;
	}
}

void Channel::setV(Client& client, std::string param, bool action)
{
	std::string reply;
	
	if (action == MODE_CHANNEL_ADD)
	{
		if (param.empty() || this->userCanTalk(param))
			return ;
		this->modes[MODE_CHANNEL_SPEAK_ABILITY] = true;
		this->_canTalk.push_back(param);
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+v", param);
		_informOnlineUsers(reply);
	}
	else
	{
		if (param.empty() || !this->userCanTalk(param))
			return ;
		this->removeTalkingPermissions(param);
		this->modes[MODE_CHANNEL_SPEAK_ABILITY] = false;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-v", param);
		_informOnlineUsers(reply);
	}
}
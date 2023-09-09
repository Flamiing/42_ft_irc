/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:36:31 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 12:56:05 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool keyAlreadySet(Client& client, std::string channelName,
		std::map<char, bool>& modes, bool action)
{
	if (modes[MODE_CHANNEL_KEY] == true && action == MODE_CHANNEL_ADD)
	{
		std::string reply = ERR_KEYSET(client.getNickname(), channelName, "Channel key already set");
		send(client.getSocket(), reply.c_str(), reply.size(), 0);
		return true;
	}
	return false;
}

void Channel::setK(Client& client, std::string param, bool action)
{
	std::string reply;
	
	if (keyAlreadySet(client, this->getName(), this->modes, action))
		return ;
	if (action == MODE_CHANNEL_REMOVE && param == this->_key)
	{
		this->modes[MODE_CHANNEL_KEY] = false;
		this->_key = "";
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-k", param);
	}
	else if (action == MODE_CHANNEL_ADD)
	{
		this->modes[MODE_CHANNEL_KEY] = true;
		this->_key = param;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+k", param);
	}
	else
	{
		reply = ERR_KEYSET(client.getNickname(), this->getName(), "Wrong key");
		send(client.getSocket(), reply.c_str(), reply.size(), 0);
		return ;
	}
	_informOnlineUsers(reply);
}
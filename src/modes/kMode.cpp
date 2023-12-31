/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:36:31 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/12 08:52:21 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool invalidKey(Client& client, std::string channelName,
		std::map<char, bool>& modes, bool action, std::string& param)
{
	std::string command;
	
	if (modes[MODE_CHANNEL_KEY] == true && action == MODE_CHANNEL_ADD)
	{
		std::string reply = ERR_KEYSET(client.getNickname(), channelName, "Channel key already set");
		send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
		return true;
	}
	else if (param.empty())
	{
		if (action == MODE_CHANNEL_ADD)
			command = "MODE +k";
		else
			command = "MODE -k";
		std::string reply = ERR_NEEDMOREPARAMS(client.getNickname(), command);
		send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
		return true;
	}
	return false;
}

void Channel::setK(Client& client, std::string param, bool action)
{
	std::string reply;
	
	if (invalidKey(client, this->getName(), this->modes, action, param))
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
		send(client.getSocket(), reply.c_str(), reply.size(), MSG_NOSIGNAL);
		return ;
	}
	_informOnlineUsers(reply);
}
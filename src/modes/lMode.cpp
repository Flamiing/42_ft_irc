/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:37:42 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 13:04:11 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Channel::setL(Client& client, std::string param, bool action)
{
	std::string reply;
	
	if (!allDigits(param) && action == MODE_CHANNEL_ADD)
		return ;
	if (action == MODE_CHANNEL_ADD)
	{
		std::stringstream ss(param);
		size_t limit;
		ss >> limit;
		if (this->_limit == limit)
			return ;
		this->modes[MODE_CHANNEL_USER_LIMIT] = true;
		this->_limit = limit;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+l", param);
		_informOnlineUsers(reply);
	}
	else if (this->modes[MODE_CHANNEL_USER_LIMIT] == true)
	{
		this->modes[MODE_CHANNEL_USER_LIMIT] = false;
		this->_limit = 0;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-l", "");
		_informOnlineUsers(reply);
	}
}
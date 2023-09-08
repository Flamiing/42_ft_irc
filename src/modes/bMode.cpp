/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:22:04 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 14:02:23 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Channel::setB(Client& client, std::string param, bool action)
{
	std::string reply;
	
	if (action == MODE_CHANNEL_ADD)
	{
		if (param.empty() || this->userIsBanned(param))
			return ;
		this->banUser(param);
		this->modes[MODE_CHANNEL_BANNED] = true;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+b", param);
		_informOnlineUsers(reply);
	}
	else
	{
		if (param.empty() || !this->userIsBanned(param))
			return ;
		this->unbanUser(param);
		this->modes[MODE_CHANNEL_BANNED] = false;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-b", param);
		_informOnlineUsers(reply);
	}
}
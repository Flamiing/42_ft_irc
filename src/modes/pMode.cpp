/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:53:14 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 03:04:52 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Channel::setP(Client& client, bool action)
{
	std::string reply;
	
	if (action == MODE_CHANNEL_ADD
		&& this->modes[MODE_CHANNEL_PRIVATE] == false)
	{
		this->modes[MODE_CHANNEL_PRIVATE] = true;
		if (this->modes[MODE_CHANNEL_SECRET] == true)
			reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-s+p", "");
		else
			reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+p", "");
		this->modes[MODE_CHANNEL_SECRET] = false;
		_informOnlineUsers(reply);
	}
	else if (action == MODE_CHANNEL_REMOVE && 
					this->modes[MODE_CHANNEL_PRIVATE] == true)
	{
		this->modes[MODE_CHANNEL_PRIVATE] = false;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-p", "");
		_informOnlineUsers(reply);
	}
}
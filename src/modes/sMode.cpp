/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:53:14 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 03:09:59 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Channel::setS(Client& client, bool action)
{
	std::string reply;
	
	if (action == MODE_CHANNEL_ADD
		&& this->modes[MODE_CHANNEL_SECRET] == false)
	{
		this->modes[MODE_CHANNEL_SECRET] = true;
		if (this->modes[MODE_CHANNEL_PRIVATE] == true)
			reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-p+s", "");
		else
			reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+s", "");
		this->modes[MODE_CHANNEL_PRIVATE] = false;
		_informOnlineUsers(reply);
	}
	else if (action == MODE_CHANNEL_REMOVE && 
					this->modes[MODE_CHANNEL_SECRET] == true)
	{
		this->modes[MODE_CHANNEL_SECRET] = false;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-s", "");
		_informOnlineUsers(reply);
	}
}
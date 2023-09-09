/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:53:14 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 02:18:40 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Channel::setI(Client& client, bool action)
{
	std::string reply;
	
	if (action == MODE_CHANNEL_ADD
		&& this->modes[MODE_CHANNEL_INVITE_ONLY] == false)
	{
		this->modes[MODE_CHANNEL_INVITE_ONLY] = true;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+i", "");
		_informOnlineUsers(reply);
	}
	else if (action == MODE_CHANNEL_REMOVE && 
					this->modes[MODE_CHANNEL_INVITE_ONLY] == true)
	{
		this->modes[MODE_CHANNEL_INVITE_ONLY] = false;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-i", "");
		_informOnlineUsers(reply);
	}
}
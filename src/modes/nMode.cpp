/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:53:14 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 02:36:15 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Channel::setN(Client& client, bool action)
{
	std::string reply;
	
	if (action == MODE_CHANNEL_ADD
		&& this->modes[MODE_CHANNEL_NO_MSG_FROM_OUTSIDE] == false)
	{
		this->modes[MODE_CHANNEL_NO_MSG_FROM_OUTSIDE] = true;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+n", "");
		_informOnlineUsers(reply);
	}
	else if (action == MODE_CHANNEL_REMOVE && 
					this->modes[MODE_CHANNEL_NO_MSG_FROM_OUTSIDE] == true)
	{
		this->modes[MODE_CHANNEL_NO_MSG_FROM_OUTSIDE] = false;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-n", "");
		_informOnlineUsers(reply);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:53:14 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 02:08:03 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Channel::setM(Client& client, bool action)
{
	std::string reply;
	
	if (action == MODE_CHANNEL_ADD
		&& this->modes[MODE_CHANNEL_MODERATED] == false)
	{
		this->modes[MODE_CHANNEL_MODERATED] = true;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "+m", "");
		_informOnlineUsers(reply);
	}
	else if (action == MODE_CHANNEL_REMOVE && 
					this->modes[MODE_CHANNEL_MODERATED] == true)
	{
		this->modes[MODE_CHANNEL_MODERATED] = false;
		reply = RPL_MODE(client.getNickname(), client.getUsername(), this->getName(), "-m", "");
		_informOnlineUsers(reply);
	}
}
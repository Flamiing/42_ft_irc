/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelBan.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:48:12 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 14:17:32 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

bool Channel::userIsBanned(std::string& nickname)
{
	std::vector<Client>::const_iterator it = this->_bannedUsers.begin();

	while (it != this->_bannedUsers.end())
	{
		if (toUpperCase((*it).getNickname()) == toUpperCase(nickname))
			return true;
		it++;
	}
	return false;
}

bool Channel::banUser(std::string& nickname)
{
	Client newBan(nickname);

	this->_bannedUsers.push_back(newBan);
	return false;
}

void Channel::unbanUser(std::string& nickname)
{
	std::vector<Client>::iterator it = this->_bannedUsers.begin();

	while (it != this->_bannedUsers.end())
	{
		if (toUpperCase((*it).getNickname()) == toUpperCase(nickname))
		{
			this->_bannedUsers.erase(it);
			break ;
		}
		it++;
	}
}
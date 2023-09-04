/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:13:49 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 12:26:17 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool Server::isBanned(Client& client, std::string& channel)
{
	std::vector<Channel>::iterator it = this->_channels.begin();
	std::string nickname(client.getNickname());

	while (it != this->_channels.end())
	{
		if ((*it).getName() == channel)
			if ((*it).userIsBanned(nickname))
				return true;
		it++;
	}
	return false;
}
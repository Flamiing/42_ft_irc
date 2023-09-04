/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:13:49 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/03 17:49:49 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

/* bool Server::isBanned(std::string& nickname, std::string& channel)
{
	std::vector<Channel>::iterator it = this->_channels.begin();

	while (it != this->_channels.end())
	{
		if ((*it).getName() == channel)
			if ((*it).userIsBanned(nickname))
				return true;
		it++;
	}
	return false;
} */
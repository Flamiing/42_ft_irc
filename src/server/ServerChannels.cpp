/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerChannels.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:13:49 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 13:31:14 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool Server::isBanned(Client& client, std::string& channel)
{
	std::vector<Channel>::iterator it = this->channels.begin();
	std::string nickname(client.getNickname());

	while (it != this->channels.end())
	{
		if (toUpperCase((*it).getName()) == toUpperCase(channel))
			if ((*it).userIsBanned(nickname))
				return true;
		it++;
	}
	return false;
}
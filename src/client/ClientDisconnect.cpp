/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDisconnect.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:19:26 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 13:36:02 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

void Client::disconnectChannels(const std::string& reply)
{
	std::vector<Channel>::iterator it = this->_joinedChannels.begin();

	while (it != this->_joinedChannels.end())
	{
		(*it).disconnectFromChannel(this->_nickname, reply);
		it++;
	}
}
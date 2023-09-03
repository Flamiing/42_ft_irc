/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelNotFound.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:49:16 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/03 16:03:03 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool channelNotFound(std::vector<Channel> channels, std::string channelToFind)
{
	std::vector<Channel>::const_iterator it = channels.begin();
	
	while (it != channels.end())
	{
		if ((*it).getName() == channelToFind)
			return false;
		it++;
	}
	return true;
}
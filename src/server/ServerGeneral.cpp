/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerGeneral.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:33:25 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 12:33:50 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Server.hpp"

bool Server::userInServer(const std::string& nickname)
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(nickname))
			return true;
		it++;
	}
	return false;
}
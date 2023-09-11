/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerGetters.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:28:13 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 12:28:48 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Server.hpp"

int Server::getPort(void) const { return this->_port; }
std::string Server::getPassword(void) const { return this->_password; }
std::map<int, Client> Server::getClients(void) const { return this->_clients; }

int Server::getSocketByNickname(const std::string nickname) const
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(nickname))
			break ;
		it++;
	}
	return it->second.getSocket();
}

Client Server::getClientByNickname(const std::string nickname) const
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(nickname))
			break ;
		it++;
	}
	return it->second;
}

Channel& Server::getChannelByName(const std::string channelName)
{
	std::vector<Channel>::iterator it = this->channels.begin();

	while (it != this->channels.end())
	{
		if (toUpperCase(it->getName()) == toUpperCase(channelName))
			break ;
		it++;
	}
	return *it;
}

std::string Server::getRawNickname(const std::string& modifiedNickname)
{
	std::map<int, Client>::const_iterator it = this->_clients.begin();

	while (it != this->_clients.end())
	{
		if (toUpperCase(it->second.getNickname()) == toUpperCase(modifiedNickname))
			return it->second.getNickname();
		it++;
	}
	return modifiedNickname;
}
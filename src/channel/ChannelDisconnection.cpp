/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDisconnection.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/15 12:58:26 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

void Channel::disconnectFromChannel(std::string client, const std::string& reply)
{
	std::vector<Client>::iterator it = this->_onlineUsers.begin();

	while (it != this->_onlineUsers.end())
	{
		if (it->getNickname() == client)
		{
			this->removeTalkingPermissions(it->getNickname());
			_removeOperator(it->getNickname());
			this->_onlineUsers.erase(it);
			break ;
		}
		it++;
	}
	_informOnlineUsers(reply);
}

std::string toLowerCase(const std::string& str)
{
	std::string result = str;
	std::string::iterator it = result.begin();
	
	while (it != result.end())
	{
		*it = std::tolower(*it);
		it++;
	}
	return result;
}

/* _GUILLE REVISAR LO DE LOS UPPER CASE Y NOMBRES CON MEDIO UPPER Y MEDO LOWER PORQUE TE LA PUEDEN LIAR */
/* _GUILLE DE UNA TACADA CUANTOS PUEDO METERLE AL CANAL */
/* _GUILLE NO TE CHEKEE PRIMERO SI ESTAS INVITED, SI NO SI YA ESTAS EN EL CHANEL */
void Channel::removeFromChannel(std::string client, const std::string& reply)
{
	std::vector<Client>::iterator it = this->_onlineUsers.begin();
	std::vector<std::string>::iterator it1 = this->_invitedUsers.begin();
	std::string lower;
	std::string upper;

	_informOnlineUsers(reply);
	while (it != this->_onlineUsers.end())
	{
		if (toUpperCase(it->getNickname()) == toUpperCase(client))
		{
			this->removeTalkingPermissions(it->getNickname());
			_removeOperator(it->getNickname());
			this->_onlineUsers.erase(it);
			for (std::vector<std::string>::iterator it3 = this->_invitedUsers.begin(); it3 != this->_invitedUsers.end(); it3++)
			{
				std::cout << *it3 << std::endl;
			}
			

			//it1 = std::find(this->_invitedUsers.begin(), this->_invitedUsers.end(), client);
			upper = toUpperCase(client);
			it1 = std::remove(this->_invitedUsers.begin(), this->_invitedUsers.end(), upper);
			std::cout << client << std::endl;
			if (it1 != this->_invitedUsers.end())
			{
				this->_invitedUsers.erase(it1);
				std::cout << "⭕⭕" << std::endl;
				break ;
			}

			lower = toLowerCase(client);
			it1 = std::remove(this->_invitedUsers.begin(), this->_invitedUsers.end(), lower);
			std::cout << client << std::endl;
			if (it1 != this->_invitedUsers.end())
			{
				this->_invitedUsers.erase(it1);
				std::cout << "⭕" << std::endl;
				break ;
			}

			break ;
		}
		it++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelGetters.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:59 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/13 12:49:56 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Channel.hpp"

std::string Channel::getName() const { return this->_name; }
size_t Channel::getUserCount() const { return this->_onlineUsers.size(); }
std::string Channel::getTopic() const { return this->_topic; }
std::string Channel::getKey() const { return this->_key; }
size_t Channel::getLimit() const { return this->_limit; }
std::vector<std::string> Channel::getInvitedUsers() const
{
	return (this->_invitedUsers);
}

std::string Channel::getOnlineUsersList()
{
	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();
	std::string listOfUsers;

	while (it != this->_onlineUsers.end())
	{
		if (checkOperator(it->getNickname()))
			listOfUsers += "@" + it->getNickname();
		else if (this->userCanTalk(it->getNickname()))
			listOfUsers += "+" + it->getNickname();
		else
			listOfUsers += it->getNickname();
		if ((it + 1) != this->_onlineUsers.end())
			listOfUsers += " ";
		it++;
	}
	return listOfUsers;
}
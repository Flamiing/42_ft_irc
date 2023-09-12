/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelSetters.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/12 12:02:28 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Channel.hpp"

void		Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

void		Channel::addOperator(std::string operatorName)
{
	this->_operators.push_back(operatorName);
}

void		Channel::addInvitedUser(std::string newInvitedUser)
{
	this->_invitedUsers.push_back(newInvitedUser);
}

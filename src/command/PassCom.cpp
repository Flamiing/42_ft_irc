/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCom.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:05:40 by guilmira          #+#    #+#             */
/*   Updated: 2023/05/02 16:10:56 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Command/PassCom.hpp"

/* CLASS DEFINITION. */
PassCom::PassCom(std::string *buffer) 
	: buffer(buffer)
{
	return ;
}
PassCom::~PassCom() { return ; }
/* --------------------------------- GET | SET --------------------------------- */

/* --------------------------------- METHODS --------------------------------- */
/* ilog = instance log */
void PassCom::ilog(const std::string & name, const std::string & msg) const
{
	
	std::cout << "[Class]PassCom	- [Instance]" << name << "	|	"\
	<< msg << std::endl;
}

void PassCom::executeCom(Server* server, Client* client, std::string& buffer, std::vector<std::string>& message)
{
	if (this->client->getAuth() == true)
	{
		buffer = ERR_ALREADYREGISTRED(this->client->getNickname());
		return ;
	}
	else if (message.size() < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(this->client->getNickname(), message[0]);
		return ;
	}
	else if (this->server->getPassword() == message[1])
		this->client->setPassAuth(true);
}
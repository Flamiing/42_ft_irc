/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:05:49 by guilmira          #+#    #+#             */
/*   Updated: 2023/04/28 23:11:31 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define	COMMAND_HPP

#include "Server.hpp"
#include "Client.hpp"
#include "commands.hpp"

/* _GUILLE get channel name _NAME command */

/* 	std::vector<Client>::const_iterator it = this->_onlineUsers.begin();
	
	while (it != this->_onlineUsers.end())
	{
		send(it->getSocket(), reply.c_str(), reply.size(), 0);
		it++;
	} */

/* CLASS DECLARATION. */
class Command
{
	public:
		Command(Server *server, Client *client, std::string *buffer, std::string& message);
		~Command();
		Command(Command const &src);

		Server		*server;
		Client		*client;
		std::string	*buffer;

		std::string raw;
		std::string cmd;
		std::vector<std::string> message;

	private:
		Command();
		Command & operator=(Command const &rhs);
};

#endif

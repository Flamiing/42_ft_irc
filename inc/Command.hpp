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



#include "generalUtils.hpp"

#include "Server.hpp"
#include "Client.hpp"

#include "commands.hpp"



/* CLASS DECLARATION. */
class Command
{
	public:
		Command(Server *server, Client *client, std::string *buffer, std::string& message);
		~Command();
		Command(Command const &src);

		std::string const &	getName() const;
		void				setName(std::string const &name);

		Server		*server;
		Client		*client;
		std::string	*buffer;

		std::string raw;
		std::string cmd;
		std::vector<std::string> message;

	private:
		Command();
		Command & operator=(Command const &rhs);
		std::string _name;

		void	ilog(const std::string & name, const std::string & msg) const;
};

#endif

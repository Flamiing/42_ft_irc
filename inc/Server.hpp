/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 01:26:34 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <map>
# include "../../inc/Clients.hpp"

# define SERVER_NAME "LOS OSADOS"
# define MAX_CLIENTS 10
//# define LOCALHOST

class Server
{
	public:
		Server(const int port, const std::string& password);
		~Server(void);

		const int getPort(void) const;
		const std::string getPassword(void) const;
	private:
		Server(void);
		Server(const Server& other);
		Server& operator=(const Server& other);
		
		const std::string _password;
		const int _port;
		int _connectedClients;
		std::map<int, Clients> _clients;
};

#endif
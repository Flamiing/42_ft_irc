/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 17:57:43 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <cstdlib>
# include <unistd.h>
# include <arpa/inet.h>
# include <poll.h>
# include <string>
# include <map>
# include <vector>
# include "Client.hpp"
# include "errors.hpp"

# define LOCALHOST "127.0.0.1"
# define SERVER_NAME "LOS-OSADOS"
# define MAX_CLIENTS 10

class Server
{
	public:
		Server(const int port, const std::string& password);
		~Server(void);

		void runServer(void);
		int getPort(void) const;
		std::string getPassword(void) const;
	private:
		Server(void);
		Server(const Server& other);
		Server& operator=(const Server& other);
		
		void _setupSever(void);
		void _handleClientConnections(void);
		void _handlePoll(void);
		void _newClient(int& clientSocket);
		void _handleClientRequest(size_t& client);

		int _port;
		std::string _password;
		std::map<int, Client> _clients;
		struct sockaddr_in _address;
		int _socket;
		std::vector<struct pollfd> _pollFds;
};

#endif
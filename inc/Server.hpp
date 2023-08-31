/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 14:36:51 by guilmira         ###   ########.fr       */
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
# include "Client.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include "IRCMessage.hpp"
# include "errors.hpp"
# include "generalUtils.hpp"
# include "commands.hpp"

# define LOCALHOST "127.0.0.1"
# define MAX_CLIENTS 10

class Server
{
	public:
		Server(const int port, const std::string& password);
		~Server(void);

		void runServer(void);
		int getPort(void) const;
		std::string getPassword(void) const;
		std::map<int, Client> getClients(void) const;
		std::vector<Channel> getChannels(void) const;
		void addChannel(std::string newChannel);
		void connectToChannel(std::string& channel, Client& client, std::string key);

		void initMapCommand(void);
		std::map<std::string, customFunctionType> mapCommand;

	private:
		Server(void);
		Server(const Server& other);
		Server& operator=(const Server& other);
		
		void _setupSever(void);
		void _handleClientConnections(void);
		void _handleClients(void);
		void _newClient(int& clientSocket);
		void _handleClientRequest(size_t& client);
		void _processMessage(const int& client, std::string message);
		void _disconnect(size_t& client);

		int _port;
		std::string _password;
		std::map<int, Client> _clients;
		struct sockaddr_in _address;
		int _socket;
		std::vector<struct pollfd> _pollFds;
		std::vector<Channel> _channels;

};

#endif
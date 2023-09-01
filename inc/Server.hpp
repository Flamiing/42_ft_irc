/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 15:26:52 by guilmira         ###   ########.fr       */
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
# include "errors.hpp"
# include "generalUtils.hpp"
# include "commands.hpp"

# define LOCALHOST "127.0.0.1"
# define MAX_CLIENTS 10
# define OPERATOR_NAME "osado"
# define OPERATOR_PASS "password"

class Server
{
	public:
		Server(const int port, const std::string& password);
		~Server(void);

		void runServer(void);
		int getPort(void) const;
		std::string getIP(void) const;
		std::string getPassword(void) const;
		std::map<int, Client> getClients(void) const;
		std::vector<Channel> getChannels(void) const;
		int getSocketByNickname(const std::string nickname) const;
		std::string getRawNickname(const std::string& modifiedNickname);
		void addChannel(std::string newChannel);
		void connectToChannel(std::string& channel, Client& client, std::string key);
		void disconnect(size_t& client);
		void disconnectClientFromChannels(std::string client, std::string& reply);
		void closeAllSockets(void);
		void _processBuffer(size_t& client, std::string& buffer);

		void initMapCommand(void);
		std::map<std::string, customFunctionType> mapCommand;

		size_t pollSize;
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

		int _port;
		std::string _password;
		std::map<int, Client> _clients;
		struct sockaddr_in _address;
		int _socket;
		std::vector<struct pollfd> _pollFds;
		std::vector<Channel> _channels;
};

#endif
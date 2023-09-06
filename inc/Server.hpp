/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 22:43:48 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <cstdlib>
# include <ctime>
# include <unistd.h>
# include <arpa/inet.h>
# include <poll.h>
# include <exception>
# include "Client.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include "errors.hpp"
# include "generalUtils.hpp"
# include "commands.hpp"
# include "colors.hpp"

# define LOCALHOST "127.0.0.1"
# define MAX_CLIENTS 10
# define OPERATOR_NAME "operator"
# define OPERATOR_PASS "password"

# define SERVER "\033[1;37m[SERVER]\033[0m"
# define SERVER_LISTENING(port) (" Listening on port " + port + "...\n")
# define CLIENT_CONNECTION(socket) (" Client connected at socket #" + socket + "\n")
# define CLIENT_DISCONNECTED(socket) (" Client at socket #" + socket + " disconnected.\n")
# define CHANNEL_DELETED(channel) (" " + channel + " has been deleted.\r\n")
# define CLIENT_MESSAGE_RECIVED(socket, message) (" Client at socket #" + socket + ": " + message + "\n")

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
		int getSocketByNickname(const std::string nickname) const;
		Client getClientByNickname(const std::string nickname) const;
		Channel getChannelByName(const std::string nickname) const;
		std::string getRawNickname(const std::string& modifiedNickname);
		void addChannel(std::string newChannel);
		void connectToChannel(std::string& channel, Client& client, std::string key);
		void disconnect(size_t& client);
		void disconnectClientFromChannels(std::string client, std::string& reply);
		void kickFromChannel(std::string& clientName, std::string& channelName, std::string& reply);
		void partFromChannel(Client& client, std::string& channelName);

		bool	isBanned(Client& client, std::string& channel);

		void closeAllSockets(void);
		bool userInServer(const std::string& nickname);

		void initMapCommand(void);
		std::map<std::string, customFunctionType> mapCommand;

		size_t pollSize;
/* _GUILLE puesto en publico por errores de compilacion */
		std::vector<Channel> channels;

	private:
		Server(void);
		Server(const Server& other);
		Server& operator=(const Server& other);
		
		void _setupSever(void);
		void _handleClientConnections(void);
		void _handleClients(void);
		void _newClient(int& clientSocket);
		void _handleClientRequest(size_t& client);
		bool _processMessage(const int& client, std::string message);
		void _processBuffer(size_t& client, std::string& buffer);
		void _removeChannelFromClient(std::string clientName, std::string& channelName);

		

		int _port;
		std::string _password;
		std::map<int, Client> _clients;
		struct sockaddr_in _address;
		int _socket;
		std::vector<struct pollfd> _pollFds;
};

#endif
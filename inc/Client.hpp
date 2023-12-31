/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:59:24 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/16 15:18:16 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
#include "Channel.hpp"
#include "Server.hpp"

class Channel;

class Client
{
	public:
		Client(void);
		Client(int socket);
		Client(std::string& nickname);
		Client(const Client& other);
		~Client(void);
		
		Client& operator=(const Client& other);

		int getSocket(void) const;
		std::string getNickname(void) const;
		std::string getWrongNickname(void) const;
		std::string getUsername(void) const;
		bool getAuth(void) const;
		bool getPassAuth(void) const;
		bool getUserAuth(void) const;
		bool getNickAuth(void) const;
		std::vector<Channel> getJoinedChannels(void) const;
		void setAsOperator(void);
		void setPassAuth(const bool auth);
		void setUserAuth(const bool auth);
		void setNickAuth(const bool auth);
		void setUsername(const std::string username);
		void setNickname(const std::string nickname);
		void setWrongNickname(const std::string nickname);
		void setFullName(const std::string fullName);
		void addToJoinedChannels(Channel& channel);
		bool isOperator(void) const;
		void removeChannel(std::string& channel);

		bool isConnectedToChannel(Channel& channel);
		
		std::string buffer;
		std::string awayMessage;
		bool isAway;

	private:
		std::string _nickname;
		std::string _wrongNickname;
		std::string _username;
		std::string _fullName;
		int _socket;
		bool _passAuth;
		bool _userAuth;
		bool _nickAuth;
		bool _auth;
		bool _isOperator;
		std::vector<Channel> _joinedChannels;
};

#endif
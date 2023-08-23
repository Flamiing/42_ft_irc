/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:59:24 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 21:33:18 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
	public:
		Client(void);
		Client(int socket);
		Client(const Client& other);
		~Client(void);
		
		Client& operator=(const Client& other);

		int getSocket(void) const;
		bool getAuth(void) const;
		bool getPassAuth(void) const;
		bool getUserAuth(void) const;

		void setPassAuth(const bool auth);
		void setUserAuth(const bool auth);
		void setUsername(const std::string username);
		void setNickname(const std::string nickname);
		void setFullName(const std::string fullName);
	private:

		std::string _nickname;
		std::string _username;
		std::string _fullName;
		int _socket;
		bool _passAuth;
		bool _userAuth;
		bool _auth;
		bool _isOperator;
};

#endif
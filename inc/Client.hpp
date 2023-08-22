/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 00:59:24 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 01:09:41 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
	public:
		~Client(void);
	private:
		Client& operator=(const Client& other);
		Client(void);
		Client(const Client& other);

		std::string _nickname;
		std::string _username;
		std::string _fullName;
		int _socket;
		bool _isOperator;
};

#endif
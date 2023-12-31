/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:57:11 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 12:35:56 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Server.hpp"

Server::Server(void) {}

Server::Server(const int port, const std::string& password) :  pollSize(0), _port(port), _password(password) {}

Server::Server(const Server& other) { (void)other; }

Server::~Server(void) {}

Server& Server::operator=(const Server& other) { (void)other; return *this; }

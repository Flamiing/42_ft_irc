/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:04:22 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 00:28:03 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../../inc/Server.hpp"
#include "../../inc/errors.hpp"
#include "../../inc/generalUtils.hpp"

int howToUse(void)
{
	std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
	return 1;
}

int main(int argc, char **argv)
{
	if (argc != 3)
		return howToUse();
	
	int port;
	if (!portParser(argv[1], port))
		return printError(BAD_PORT);
	Server server(port, argv[2]);
	server.startServer();
	return 0;
}
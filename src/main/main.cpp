/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:04:22 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/03 15:48:27 by alaaouam         ###   ########.fr       */
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
	try
	{
		int port;
		std::string password(argv[2]);
		std::string portStr(argv[1]);
		if (!parsePort(portStr, port))
			return printError(BAD_PORT, NORMAL);
		Server server(port, password);
		server.runServer();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}
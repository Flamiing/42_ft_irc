/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:35:46 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/23 16:17:39 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"

void passCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (message.size() > 2)
	{
		buffer = "PASS: ";
		buffer += WRONG_NUM_ARGS;
		return ;
	}
	else if (server.getPassword() != message[1])
	{
		buffer = WRONG_PASS;
		return ;
	}
	else
		client.setPassAuth(true);
}
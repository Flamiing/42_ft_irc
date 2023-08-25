/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:35:46 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/25 12:28:05 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/Client.hpp"

void passCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (client.getAuth() == true)
	{
		buffer = ERR_ALREADYREGISTRED(client.getNickname());
		return ;
	}
	else if (message.size() < 2)
	{
		buffer = ERR_NEEDMOREPARAMS(client.getNickname(), message[0]);
		return ;
	}
	else if (server.getPassword() == message[1])
		client.setPassAuth(true);
}
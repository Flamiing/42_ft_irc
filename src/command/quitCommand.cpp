/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:44:22 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/31 12:44:20 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/Command.hpp"





/* _GUILLE Borrador, mantener de momento */

/* static void quitCommand(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC)
{
	std::string user_message;
	std::string full_message;

	full_message = messageIRC.raw;
	//full_message = messageIRC.getRaw();

	size_t clientFd;
	clientFd = client.getSocket();

	user_message = full_message.substr(full_message.find(" "));
	buffer = RPL_QUIT(client.getNickname(), client.getUsername(), user_message);
	server._disconnect(&clientFd);
} */
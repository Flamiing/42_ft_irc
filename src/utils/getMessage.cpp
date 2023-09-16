/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:30:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/16 16:20:22 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

std::string getMessageToSend(Command& command, size_t messagePos)
{
	std::vector<std::string> remove;
	std::string messageToSend;
	remove.push_back(command.cmd);
	if (command.cmd != QUIT && command.cmd != AWAY)
		remove.push_back(command.message[1]);
	
	if (command.message[messagePos][0] != ':')
		return command.message[command.message.size() - 1];
	else
		messageToSend = getMessage(command.raw, remove);
	if (messageToSend[0] == ':')
		messageToSend.erase(0, 1);
	return messageToSend;
}

std::string getMessage(const std::string& raw, const std::vector<std::string>& remove)
{
	std::string newString(raw);
	std::vector<std::string>::const_iterator it = remove.begin();
	size_t pos = 0;
	
	while (it != remove.end())
	{
		trimSpaces(newString);
		pos = newString.find(*it, 0);
		if (pos != std::string::npos)
			newString.erase(pos, (*it).length());
		it++;
	}
	trimSpaces(newString);
	return newString;
}

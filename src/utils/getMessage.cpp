/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:30:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 19:18:27 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

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


/* _GUILLE - para mensajes generales */
std::string displayMsg(std::string number, std::string str, std::string clientNick)
{
	return (std::string(":localhost " + number + " " + clientNick + " " + str + "\r\n") );
}
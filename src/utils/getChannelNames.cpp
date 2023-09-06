/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getChannelNames.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:40:36 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 22:46:33 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

static bool hasWhiteSpace(const std::string& str)
{
	size_t pos = 0;
	
	while (pos != str.size())
	{
		if (isspace(str[pos]))
			return true;
		pos++;
	}
	return false;
}

static std::string removeFromSpace(const std::string& str)
{
	std::string newString;
	size_t pos = 0;

	while (pos < str.size())
	{
		if (isspace(str[pos]))
			break ;
		newString.push_back(str[pos]);
		pos++;
	}
	if (pos == 0)
		return str;
	return newString;
}

std::vector<std::string> getChannelNames(std::string& raw)
{
	std::vector<std::string> remove;
	remove.push_back(PART);
	std::string commaSeparated = getMessage(raw, remove);
	commaSeparated = trimSpaces(commaSeparated);
	std::vector<std::string> channels = splitString(commaSeparated, ',');
	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator end = channels.end();
	bool whiteSpaceFound = false;
	
	while (it != end)
	{
		if (hasWhiteSpace(*it))
		{
			whiteSpaceFound = true;
			*it = removeFromSpace(*it);
			it++;
			break ;
		}
		it++;
	}
	if (whiteSpaceFound)
		channels.erase(it, end);
	return channels;
}
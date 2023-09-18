/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toUpperCase.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:10:37 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/16 19:55:31 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

std::string toUpperCase(const std::string& str)
{
	std::string result = str;
	std::string::iterator it = result.begin();
	
	while (it != result.end())
	{
		*it = std::toupper(*it);
		it++;
	}
	return result;
}

bool isEqualStr(std::string str1, std::string str2)
{
	std::string string = toUpperCase(str1);

	if (!string.compare(toUpperCase(str2)))
		return true;
	else
		return false;
}

bool isLowerCase(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	return false;
}

void toUpperCaseCmd(std::string& str)
{
	size_t pos = 0;
	
	while (pos < str.size() && !isspace(str[pos]))
	{
		if (isLowerCase(str[pos]))
			str[pos] = std::toupper(str[pos]);
		pos++;
	}
}

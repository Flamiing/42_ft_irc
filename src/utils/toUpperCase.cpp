/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toUpperCase.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:10:37 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 15:48:06 by guilmira         ###   ########.fr       */
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

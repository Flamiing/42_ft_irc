/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsePort.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:25:14 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 12:50:23 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool allDigits(const std::string& str)
{
	if (str.empty())
		return false;
	size_t pos = 0;
	while (pos < str.length())
	{
		if (str[pos] < '0' || str[pos] > '9')
			return false;
		pos++;
	}
	return true;
}

bool parsePort(std::string& portStr, int& port)
{
	if (portStr.length() > 5)
		return false;
	else if (!allDigits(portStr))
		return false;
	port = atoi(portStr.c_str());
	if (port == 0 || port > 65535)
		return false;
	else
		return true;
}
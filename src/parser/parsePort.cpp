/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsePort.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:25:14 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/21 22:38:15 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../../inc/errors.hpp"

static bool allDigits(const std::string& str)
{
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
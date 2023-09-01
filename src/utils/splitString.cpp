/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitString.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:17:10 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 04:03:22 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/generalUtils.hpp"

std::vector<std::string> splitString(std::string& str, char delimiter)
{
	std::vector<std::string> splitted;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter))
	{
		if (!token.empty())
			splitted.push_back(token);
	}
	return splitted;
}

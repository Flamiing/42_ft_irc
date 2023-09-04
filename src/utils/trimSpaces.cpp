/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimSpaces.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:34 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 02:17:44 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

std::string trimSpaces(std::string& str)
{
	size_t count = 0;
	while (count < str.size())
	{
		if (!isspace(str[0]))
			return str;
		else
			str.erase(0, 1);
		count++;
	}
	return str;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimSpaces.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:34 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 19:34:36 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/generalUtils.hpp"

std::string trimSpaces(std::string& str)
{
	size_t count = 0;
	while (count < str.size())
	{
		if (str[0] != ' ')
			return str;
		else
			str.erase(0, 1);
		count++;
	}
	return str;
}
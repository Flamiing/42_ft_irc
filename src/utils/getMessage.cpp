/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:30:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 20:51:36 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/generalUtils.hpp"

std::string getMessage(const std::string& raw, const std::vector<std::string>& remove)
{
	std::string newString(raw);
	std::vector<std::string>::const_iterator it = remove.begin();
	size_t pos = 0;
	
	while (it != remove.end())
	{
		trimSpaces(newString);
		pos = newString.find(*it, 0);
		newString.erase(pos, (*it).length());
		it++;
	}
	trimSpaces(newString);
	return newString;
}
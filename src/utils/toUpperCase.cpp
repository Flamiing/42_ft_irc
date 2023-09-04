/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toUpperCase.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:10:37 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 02:17:41 by alaaouam         ###   ########.fr       */
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
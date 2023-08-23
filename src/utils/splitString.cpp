/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitString.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:17:10 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 19:20:09 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/generalUtils.hpp"

std::vector<std::string> splitString(std::string& str, char delimiter)
{
	std::vector<std::string> splitted;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter))
		splitted.push_back(token);	
	return splitted;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numberToString.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:08:25 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 01:09:48 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

std::string numberToString(const size_t number)
{
	std::stringstream ss;
	ss << number;
	std::string string(ss.str());

	return string;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printError.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:31:08 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/04 02:16:20 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

int printError(const std::string error, int mode)
{
	if (mode == NORMAL)
		std::cerr << error << std::endl;
	else
		std::cerr << error << strerror(errno) << std::endl;
	return 1;
}
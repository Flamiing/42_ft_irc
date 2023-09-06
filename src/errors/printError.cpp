/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printError.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:31:08 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 00:46:26 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

int printError(const std::string error, int mode)
{
	if (mode == NORMAL)
		std::cerr << BOLD_RED << error << RESET << std::endl;
	else
		std::cerr << BOLD_RED << error << strerror(errno) << RESET << std::endl;
	return 1;
}
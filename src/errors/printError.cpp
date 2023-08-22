/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printError.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:31:08 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 14:25:43 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../../inc/errors.hpp"

int printError(const std::string error, int mode)
{
	if (mode == NORMAL)
		std::cerr << error << std::endl;
	else
		std::cerr << error << strerror(errno) << std::endl;
	return 1;
}
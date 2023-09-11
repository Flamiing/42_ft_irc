/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientOperator.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:05:57 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 11:06:17 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

bool Client::isOperator(void) const { return this->_isOperator; }

void Client::setAsOperator(void)
{
	this->_isOperator = true;
}
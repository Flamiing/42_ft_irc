/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:27:35 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/23 16:17:39 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands.hpp"

void userCommand(Client& client, std::string& buffer, std::vector<std::string>& message)
{
	if (client.getAuth() == true)
		return ;
	if (message.size() > 6)
	{
		buffer = WRONG_NUM_ARGS;
		return ;
	}
	client.setUserAuth(true);
	client.setUsername(message[1]);
	client.setNickname(message[1]);
	std::string fullName = message[4].c_str() + 1;
	fullName += " " + message[5];
	client.setFullName(fullName);
}
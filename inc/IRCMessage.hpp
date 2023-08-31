/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:12:33 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 19:05:09 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include "generalUtils.hpp"

class IRCMessage
{
	public:
		IRCMessage(std::string& message);
		IRCMessage(const IRCMessage& other);
		~IRCMessage(void);

		IRCMessage& operator=(const IRCMessage& other);

		std::string raw;
		std::string cmd;
		std::vector<std::string> vector;
	private:
		IRCMessage(void);
};

#endif
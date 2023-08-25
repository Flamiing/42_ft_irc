/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/24 22:51:01 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "../../inc/Client.hpp"

class Channel
{
	public:
		Channel(std::string& name);
		~Channel(void);

		Channel& operator=(const Channel& other);
	private:
		Channel(void);
		Channel(const Channel& other);
		
		std::string _name;
		std::string _topic;
		std::string _creationDate;
		std::vector<Client> _onlineUsers;
};

#endif
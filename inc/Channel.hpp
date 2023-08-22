/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/22 13:07:34 by alaaouam         ###   ########.fr       */
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
		~Channel(void);

	private:
		Channel(void);
		Channel(const Channel& other);
		Channel& operator=(const Channel& other);
		
		std::string _topic;
		std::vector<Client> _onlineUsers;
		size_t _onlineUsersCount;
};

#endif
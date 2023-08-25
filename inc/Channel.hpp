/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/25 19:41:38 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include "Client.hpp"
# include "commands.hpp"

class Channel
{
	public:
		Channel(void);
		Channel(std::string& name);
		Channel(const Channel& other);
		~Channel(void);

		Channel& operator=(const Channel& other);

		std::string getName(void) const;
		std::string getTopic(void) const;
		std::string getKey(void) const;
		std::string getOnlineUsersList(void) const;
		void _replyToNewUser(Client& client);
		void _informOnlineUsers(Client& client);
		void joinChannel(Client& client, std::string& key);
	private:
		
		std::string _name;
		std::string _key;
		std::string _topic;
		std::vector<Client> _onlineUsers;
};

#endif
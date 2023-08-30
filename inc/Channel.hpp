/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 13:44:04 by alaaouam         ###   ########.fr       */
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
		std::vector<Client> getBannedUsers(void) const;
		void _replyToNewUser(Client& client);
		void _informOnlineUsers(const std::string& reply);
		void joinChannel(Client& client, std::string& key);
		bool userIsBanned(std::string& nickname);
	private:
		
		std::string _name;
		std::string _key;
		std::string _topic;
		std::vector<Client> _onlineUsers;
		std::vector<Client> _bannedUsers;
};

#endif
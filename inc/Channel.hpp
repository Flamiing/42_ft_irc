/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/01 16:37:38 by guilmira         ###   ########.fr       */
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
		void joinChannel(Client& client, std::string& key);
		bool userIsBanned(std::string& nickname);
		bool clientInChannel(std::string& nickname);
		void disconnectFromChannel(std::string& client, const std::string& reply);

		std::string		getMode() const
		{
			return (this->_mode);
		}

		void setTopic(std::string new_topic)
		{
			this->_topic = new_topic;
		}

	private:
		void _informOnlineUsers(const std::string& reply);
		void _replyToNewUser(Client& client);
		
		std::string _name;
		std::string _key;
		std::string _topic;

		std::string _mode;

		std::vector<Client> _onlineUsers;
		std::vector<Client> _bannedUsers;
};

#endif
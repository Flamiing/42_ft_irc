/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 16:55:29 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include "Client.hpp"
# include "commands.hpp"

# define MODE_CHANNEL_OPERATOR 'o'
# define MODE_CHANNEL_PRIVATE 'p'
# define MODE_CHANNEL_SECRET 's'
# define MODE_CHANNEL_INVITE_ONLY 'i'
# define MODE_CHANNEL_TOPIC_OPER_ONLY 't'
# define MODE_CHANNEL_NO_MSG_FROM_OUTSIDE 'n'
# define MODE_CHANNEL_MODERATED 'm'
# define MODE_CHANNEL_USER_LIMIT 'l'
# define MODE_CHANNEL_BANNED 'b'
# define MODE_CHANNEL_SPEAK_ABILITY 'v'
# define MODE_CHANNEL_KEY 'k'

class Channel
{
	public:
		Channel(void);
		Channel(std::string& name, std::string& key);
		Channel(const Channel& other);
		~Channel(void);

		Channel& operator=(const Channel& other);

		std::string getName(void) const;
		size_t getUserCount(void) const;
		std::string getTopic(void) const;
		void		setTopic(std::string topic);
		std::string getKey(void) const;
		size_t getLimit(void) const;
		std::string getOnlineUsersList(void) const;
		std::vector<Client> getBannedUsers(void) const;
		void joinChannel(Client& client, std::string& key, std::string& buffer);
		bool userIsBanned(std::string& nickname);
		bool clientInChannel(std::string nickname);
		void disconnectFromChannel(std::string client, const std::string& reply);
		void removeFromChannel(std::string client, const std::string& reply);
		void messageOnlineUsers(const std::string sender, const std::string& reply);
		

		bool isClientOperator(Client& client);

		bool isUserInChannel();

		std::map<char, bool> modes;
		std::string creationTime;
	private:
		void _informOnlineUsers(const std::string& reply);
		void _replyToNewUser(Client& client);
		
		std::string _name;
		size_t		_userCount;
		std::string _key;
		std::string _topic;
		size_t _limit;

		std::vector<Client> _onlineUsers;
		std::vector<Client> _bannedUsers;
};

#endif
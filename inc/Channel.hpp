/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 02:36:32 by alaaouam         ###   ########.fr       */
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
# define MODE_CHANNEL_ADD true
# define MODE_CHANNEL_REMOVE false

class Channel;

typedef void (Channel::*modeWithParamsFunctions)(Client& client, std::string param, bool action);
typedef void (Channel::*modeFunctions)(Client& client, bool action);

class Channel
{
	public:
		Channel(void);
		Channel(std::string& name);
		Channel(const Channel& other);
		~Channel(void);

		Channel& operator=(const Channel& other);

		std::string getName(void) const;
		size_t getUserCount(void) const;
		std::string getTopic(void) const;
		std::string getKey(void) const;
		size_t getLimit(void) const;
		std::string getOnlineUsersList(void) ;
		std::vector<Client> getBannedUsers(void) const;
		void joinChannel(Client& client, std::string& key);
		bool userIsBanned(std::string& nickname);
		bool banUser(std::string& nickname);
		void unbanUser(std::string& nickname);
		bool userCanTalk(std::string nickname);
		void removeTalkingPermissions(std::string nickname);
		
		void setMode(Client& client, char mode, std::string param, bool action);
		void setO(Client& client, std::string param, bool action);
		void setK(Client& client, std::string param, bool action);
		void setL(Client& client, std::string param, bool action);
		void setB(Client& client, std::string param, bool action);
		void setV(Client& client, std::string param, bool action);
		void setM(Client& client, bool action);
		void setI(Client& client, bool action);
		void setT(Client& client, bool action);
		void setN(Client& client, bool action);

		void setTopic(std::string new_topic)
		{
			this->_topic = new_topic;
		}

		bool clientInChannel(std::string nickname);
		void disconnectFromChannel(std::string client, const std::string& reply);
		void removeFromChannel(std::string client, const std::string& reply);
		void messageOnlineUsers(const std::string sender, const std::string& reply);
		
		std::map<char, bool> modes;
		std::string creationTime;
		std::map<char, modeWithParamsFunctions> modesWithParams;
		std::map<char, modeFunctions> modesWithoutParams;
	private:
		void _informOnlineUsers(const std::string& reply);
		void _replyToNewUser(Client& client);
		bool _checkOperator(std::string client);
		void _removeOperator(std::string operatorToRemove);
		
		std::string _name;
		std::string _key;
		std::string _topic;
		size_t _limit;

		std::vector<std::string> _operators;
		std::vector<std::string> _canTalk;
		std::vector<Client> _onlineUsers;
		std::vector<Client> _bannedUsers;
};

#endif
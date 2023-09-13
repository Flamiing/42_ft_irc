/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:02:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/13 12:50:32 by guilmira         ###   ########.fr       */
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
# define MAX_CHANNELS_PER_CLIENT 3

class Channel;

typedef void (Channel::*modeWithParamsFunctions)(Client& client, std::string param, bool action);
typedef void (Channel::*modeFunctions)(Client& client, bool action);

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
		std::string getOnlineUsersList(void) ;
		std::vector<Client> getBannedUsers(void) const;
		std::vector<std::string> getInvitedUsers(void) const;

		void	joinChannel(Client& client, std::string& key, std::string& buffer);
		bool	userIsBanned(std::string& nickname);
		bool	banUser(std::string& nickname);
		void	unbanUser(std::string& nickname);
		bool	userCanTalk(std::string nickname);
		void	removeTalkingPermissions(std::string nickname);
		
		void	setMode(Client& client, char mode, std::string param, bool action);
		void	setO(Client& client, std::string param, bool action);
		void	setK(Client& client, std::string param, bool action);
		void	setL(Client& client, std::string param, bool action);
		void	setB(Client& client, std::string param, bool action);
		void	setV(Client& client, std::string param, bool action);
		void	setM(Client& client, bool action);
		void	setI(Client& client, bool action);
		void	setT(Client& client, bool action);
		void	setN(Client& client, bool action);
		void	setP(Client& client, bool action);
		void	setS(Client& client, bool action);
		
		bool	clientInChannel(std::string nickname);
		void	disconnectFromChannel(std::string client, const std::string& reply);
		void	removeFromChannel(std::string client, const std::string& reply);
		void	messageOnlineUsers(const std::string sender, const std::string& reply);
		bool	checkOperator(std::string client);
		bool	isClientOperator(Client& client);
		bool	isUserInChannel(void);


		void	addOperator(std::string operatorName);
		void	addInvitedUser(std::string newInvitedUser);

		std::map<char, bool> modes;
		std::string creationTime;
		std::map<char, modeWithParamsFunctions> modesWithParams;
		std::map<char, modeFunctions> modesWithoutParams;
	private:
		void _initChannelModes(void);
		void _initModeFunctions(void);
		void _informOnlineUsers(const std::string& reply);
		void _replyToNewUser(Client& client);
		void _removeOperator(std::string operatorToRemove);
		
		std::string						_name;
		size_t							_userCount;
		std::string						_key;
		std::string						_topic;
		size_t							_limit;
		static int						_nbChannels;

		std::vector<std::string>		_operators;
		std::vector<std::string>		_canTalk;
		std::vector<std::string> 		_invitedUsers;
		std::vector<Client>				_onlineUsers;
		std::vector<Client>				_bannedUsers;
};

# include "copyTemplates.tpp"

#endif
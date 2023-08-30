/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:48:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 19:20:59 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <vector>
# include <string>
# include <sys/socket.h>
# include "generalUtils.hpp"

class Server;
class Client;
class Channel;
class IRCMessage;

# define PASS "PASS"
# define NICK "NICK"
# define USER "USER"
# define PRIVMSG "PRIVMSG"
# define NOTICE "NOTICE"
# define HELP "HELP"
# define OPER "OPER"
# define KICK "KICK"
# define JOIN "JOIN"
# define TOPIC "TOPIC"
# define QUIT "QUIT"
# define PONG "PONG"

# define RPL_WELCOME(client) (":localhost 001 " + client + " :Welcome to LOS OSADOS IRC Server, " + client + "!\r\n")
# define RPL_TOPIC(client, channel, topic) (":localhost 332 " + client + " #" + channel + " :" + topic + "\r\n")
# define RPL_NAMREPLY(client, symbol, channel, list) (":localhost 353 " + client + " " + symbol + " #" + channel + " :" + list + "\r\n")
# define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " #" + channel + " :End of /NAMES list.\r\n")
# define ERR_NORECIPIENT(client, command) (":localhost 411 " + client + " :No recipient given (" + command + ")\r\n")
# define ERR_NOTEXTTOSEND(client) (":localhost 412 " + client + " :No text to send\r\n")
# define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command\r\n")
# define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(client, erroneousNickname) (":localhost 432 " + client + " " + erroneousNickname + " :Erroneous nickname\r\n")
# define ERR_NICKNAMEINUSE(client, nicknameInUse) (":localhost 433 " + client + " " + nicknameInUse + " :Nickname is already in use\r\n")
# define ERR_NOTREGISTERED(client) (":localhost 451 " + client + " :You have not registered\r\n")
# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTRED(client) (":localhost 462 " + client + " :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect\r\n")
# define ERR_INVITEONLYCHAN(client, channel) (":localhost 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
# define ERR_BANNEDFROMCHAN(client, channel) (":localhost 474 " + client + " " + channel + " :Cannot join channel (+b)\r\n")
# define RPL_NICKNAMECHANGED(nickname, username, newNickname) (":" + nickname + "!~" + username + "@localhost NICK :" + newNickname + "\r\n")
# define RPL_USERJOINEDCHANNEL(nickname, username, channel) (":" + nickname + "!~" + username + "@localhost JOIN #" + channel + "\r\n")
# define RPL_QUIT(nickname, username, message) (":" + nickname + "!~" + username + "@localhost QUIT :Quit: " + message + "\r\n")
# define MSG_NOTICE(nickname, username, recipient, message) (":" + nickname + "!~" + username + "@localhost NOTICE " + recipient + " :" + message + "\r\n")

void processCommand(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC);
void passCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message);
void nickCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message);
void userCommand(Client& client, std::string& buffer, std::vector<std::string>& message);
void joinCommand(Server& server, Client& client, std::string& buffer, std::vector<std::string>& message);
void quitCommand(Client& client, std::string& buffer, std::vector<std::string>& message);
void noticeCommand(Server& server, Client& client, std::string& buffer, IRCMessage& messageIRC);
//void privmsgCommand(Client& client, std::string& buffer, std::vector<std::string>& message);

#endif
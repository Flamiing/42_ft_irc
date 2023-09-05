/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:48:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 13:55:34 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <map>

class Server;
class Client;
class Channel;
class Command;

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
# define PART "PART"
# define DIE "DIE"

# define RPL_WELCOME(client) (":localhost 001 " + client + " :Welcome to LOS OSADOS IRC Server, " + client + "!\r\n")
# define RPL_NAMREPLY(client, symbol, channel, list) (":localhost 353 " + client + " " + symbol + " " + channel + " :" + list + "\r\n")
# define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " " + channel + " :End of /NAMES list.\r\n")
# define RPL_YOUREOPER(client) (":localhost 381 " + client + " :You are now an IRC operator\r\n")
# define ERR_NOSUCHNICK(client, nickname) (":localhost 401 " + client + " " + nickname + " :No such nick\r\n")
# define ERR_NOSUCHCHANNEL(client, channel) (":localhost 403 " + client + " " + channel + " :No such channel\r\n")
# define ERR_CANNOTSENDTOCHAN(client, channel) (":localhost 404 " + client + " " + channel + " :Cannot send to channel\r\n")
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
# define ERR_INVALIDUSERNAME(client) (":localhost 468 " + client + ":Your username is invalid\r\n")
# define ERR_INVITEONLYCHAN(client, channel) (":localhost 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
# define ERR_BANNEDFROMCHAN(client, channel) (":localhost 474 " + client + " " + channel + " :Cannot join channel (+b)\r\n")
# define ERR_NOPRIVILEGES(client) (":localhost 481 " + client + " :Permission Denied- You're not an IRC operator\r\n")
# define ERR_NOOPERHOST(client) (":localhost 491 " + client + " :No O-lines for your host\r\n")
# define RPL_NICKNAMECHANGED(nickname, username, newNickname) (":" + nickname + "!~" + username + "@localhost NICK :" + newNickname + "\r\n")
# define RPL_USERJOINEDCHANNEL(nickname, username, channel) (":" + nickname + "!~" + username + "@localhost JOIN " + channel + "\r\n")
# define RPL_QUITWITHNOMSG(nickname, username) (":" + nickname + "!~" + username + "@localhost QUIT :Quit\r\n")
# define RPL_QUITWITHEOF(nickname, username) (":" + nickname + "!~" + username + "@localhost QUIT EOF from client\r\n")
# define RPL_QUIT(nickname, username, message) (":" + nickname + "!~" + username + "@localhost QUIT :Quit: " + message + "\r\n")
# define RPL_KICKWITHNOMSG(nickname, username, channel, kicked) (":" + nickname + "!~" + username + "@localhost KICK " + channel + " " + kicked + " :" + kicked + "\r\n")
# define RPL_KICKWITHMSG(nickname, username, channel, kicked, message) (":" + nickname + "!~" + username + "@localhost KICK " + channel + " " + kicked + " " + message + "\r\n")
# define RPL_NOTICE(nickname, username, recipient, message) (":" + nickname + "!~" + username + "@localhost NOTICE " + recipient + " :" + message + "\r\n")
# define RPL_PRIVMSG(nickname, username, recipient, message) (":" + nickname + "!~" + username + "@localhost PRIVMSG " + recipient + " :" + message + "\r\n")
# define RPL_HELP(client) (":localhost 000 " + client + " :Use the following commands to traverse the chat: \r\n")
# define RPL_PART(nickname, username, channel) (":" + nickname + "!~" + username + "@localhost PART " + channel + "\r\n")


typedef void (*customFunctionType)(Command& command);

void privmsgCommand(Command& command);
void processCommand(Command& command);
void passCommand(Command& command);
void userCommand(Command &command);
void nickCommand(Command &command);
void joinCommand(Command &command);
void noticeCommand(Command &command);
void quitCommand(Command &command);
void operCommand(Command& command);
void dieCommand(Command& command);
void kickCommand(Command& command);
void partCommand(Command& command);
/* void privmsgCommand(Command &command); */
void topicCommand(Command &command);
# define RPL_TOPIC(client, channel, topic) (":localhost 332 " + client + " " + channel + " :" + topic + "\r\n")
# define RPL_NOTOPIC(client, channel) (":localhost 331 " + client + " " + channel + " :No topic is set\r\n")
# define ERR_CHANOPRIVSNEEDED(client, channel) (":localhost 482 " + client + " " + channel + " :You're not channel operator\r\n")
# define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " " + channel + " :You're not on that channel\r\n")
/* # define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " #" + channel " :You're not on that channel\r\n") */
/* _GUILLE el de abajo no funciona? ponemos con hastag el channel si o no */


std::string displayMsg(std::string number, std::string str, std::string clientNick);

#endif
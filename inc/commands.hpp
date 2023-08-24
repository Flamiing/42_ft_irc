/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:48:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/24 21:40:46 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Client.hpp"

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

# define RPL_WELCOME(client) (":localhost 001 " + client + " :Welcome to LOS OSADOS IRC Server, " + client + "!\r\n")
# define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command\r\n")
# define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(client, erroneousNickname) (":localhost 432 " + client + " " + erroneousNickname + " :Erroneous nickname\r\n")
# define ERR_NICKNAMEINUSE(client, nicknameInUse) (":localhost 433 " + client + " " + nicknameInUse + " :Nickname is already in use\r\n")
# define ERR_NOTREGISTERED(client) (":localhost 451 " + client + " :You have not registered\r\n")
# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTRED(client) (":localhost 462 " + client + " :You may not reregister\r\n")
# define RPL_NICKNAMECHANGED(nickname, username, newNickname) (":" + nickname + "!~" + username + "@localhost NICK :" + newNickname + "\r\n")

#endif
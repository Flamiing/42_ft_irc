/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:48:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/24 00:28:39 by alaaouam         ###   ########.fr       */
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

# define INVALID_CMD "Invalid command\r\n"
# define WRONG_NUM_ARGS "wrong number of arguments.\r\n"
# define WRONG_PASS "PASS: wrong password.\r\n"

# define RPL_NOTAUTHENTICATED ":localhost 998 * :You need to authenticate first\r\n"
# define ERR_ALREADYREGISTRED ":localhost 461 * :You may not reregister\r\n"
# define ERR_NEEDMOREPARAMS(command) (":localhost 462 * " + command + " :Not enough parameters.\r\n")

#endif
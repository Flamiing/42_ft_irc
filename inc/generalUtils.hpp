/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalUtils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:37:45 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/08 12:42:39 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERALUTILS_CPP
# define GENERALUTILS_CPP

# include <iostream>
# include <sstream>
# include <string>
# include <vector>

class Server;
class Channel;
class Client;
class Command;

bool parsePort(std::string& portStr, int& port);
std::vector<std::string> splitString(std::string& str, char delimiter);
std::string getMessage(const std::string& raw, const std::vector<std::string>& remove);
std::string trimSpaces(std::string& str);
std::string toUpperCase(const std::string& str);
bool channelNotFound(std::vector<Channel> channels, std::string channelToFind);
bool notInChannel(Client& client, std::string& channelName);
bool findChannels(Client& client, std::vector<Channel> channels, std::vector<std::string>& channelsToFind);
std::string numberToString(const size_t number);
std::string getMessageToSend(Command& command, size_t messagePos);
bool userNotInChannel(Server& server, std::string nickname, std::string& channelName);
std::vector<std::string> getChannelNames(std::string& raw);
std::string getCurrentTime(void);
bool allDigits(const std::string& str);

#endif
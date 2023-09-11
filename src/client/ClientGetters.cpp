/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientGetters.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:04:49 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/11 11:05:24 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Client.hpp"

int Client::getSocket(void) const { return this->_socket; }
std::string Client::getUsername(void) const { return this->_username; }
std::string Client::getNickname(void) const { return this->_nickname; }
std::string Client::getWrongNickname(void) const { return this->_wrongNickname; }
bool Client::getPassAuth(void) const { return this->_passAuth; }
bool Client::getUserAuth(void) const { return this->_userAuth; }
bool Client::getNickAuth(void) const { return this->_nickAuth; }
bool Client::getAuth(void) const { return this->_auth; }
std::vector<Channel> Client::getJoinedChannels(void) const { return this->_joinedChannels; }
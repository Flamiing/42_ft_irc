/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:05:40 by guilmira          #+#    #+#             */
/*   Updated: 2023/05/02 16:10:56 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Command.hpp"

/* CLASS DEFINITION. */
/* --------------------------------- CONSTRUCTORS --------------------------------- */
Command::Command()
	: server(NULL), client(NULL), buffer(NULL), raw(" ")
{
	return ;
}

/* Stringstream is used to be able to manipulate the string in get line and 
split into the first token. then split string does a split on the message */
Command::Command(Server *server, Client *client, std::string *buffer, std::string& message)
	: server(server), client(client), buffer(buffer)
{	
	if (!message.empty())
	{
		this->message = splitString(message, ' ');
		this->cmd = this->message[0];
		this->raw = trimSpaces(message);
	}
	else
		message = "EMPTY COMMAND"; /* _GUILLE ¿CUmple protocolo? */
	
}

/* --------------------------------- DESTRUCTOR --------------------------------- */
Command::~Command()
{
	return ;
}
/* ------------------COPY CONSTRUCTOR AND ASSIGN OVERLOAD OPERATOR------------------ */
Command::Command(Command const &src)
{
	*this = src;
	return ;
}

Command & Command::operator=(Command const &rhs)
{
	(void) rhs;
	return (*this);
}
/* --------------------------------- GET | SET --------------------------------- */

/* --------------------------------- METHODS --------------------------------- */

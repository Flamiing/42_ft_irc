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
	: server(NULL), client(NULL), buffer(" "), raw(" "), _name("Default")
{
	ilog(getName(), "Constructed⚪");
	return ;
}

/* Stringstream is used to be able to manipulate the string in get line and 
split into the first token. then split string does a split on the message */
Command::Command(Server *server, Client *client, std::string& buffer, std::string& message)
	: server(server), client(client), buffer(buffer), raw(message)
{
	std::stringstream	ss(message);
	std::string			token;

	std::getline(ss, token, ' ');
	this->cmd = token;
	this->message = splitString(message, ' ');

//_GUILLE
	this->_name = token;
	ilog(getName(), "Constructed⚪");
}

/* --------------------------------- DESTRUCTOR --------------------------------- */
Command::~Command()
{
	ilog(getName(), "-Destroyed⭕");
	return ;
}
/* White and red dots means default constructed or destructed */
/* ------------------COPY CONSTRUCTOR AND ASSIGN OVERLOAD OPERATOR------------------ */
Command::Command(Command const &src)
{
	*this = src;
	ilog(getName(), "Copy constructed");
	return ;
}
//_GUILLE falt copiar referencias, deep copy?
/* Overload actually is previous to copy constructor, since cc uses the assign operator. */
Command & Command::operator=(Command const &rhs)
{
	ilog(getName(), "[=] Assignation operator called");
	if (this != &rhs)
	{
		this->raw = rhs.raw;
		this->cmd = rhs.cmd;
		
		size_t pos = 0;
		while (pos < rhs.message.size())
		{
			this->message.push_back(rhs.message[pos]);
			pos++;
		}
		this->setName(rhs.getName());
	}
	return (*this);
}
/* --------------------------------- GET | SET --------------------------------- */
std::string const & Command::getName() const
{
	return (this->_name);
}

void Command::setName(std::string const &name)
{ 
	this->_name = name;
}
/* --------------------------------- METHODS --------------------------------- */
/* ilog = instance log */
void Command::ilog(const std::string & name, const std::string & msg) const
{
	
	std::cout << "[Class]Command	- [Instance]" << name << "	|	"\
	<< msg << std::endl;
}

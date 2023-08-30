/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCom.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:05:49 by guilmira          #+#    #+#             */
/*   Updated: 2023/04/28 23:11:31 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCOM_HPP
#define	PASSCOM_HPP

#include <iostream>
#include <string>

# include "../Command.hpp"



/* CLASS DECLARATION. */
class PassCom : public Command
{
	public:
		PassCom(std::string *buffer);
		~PassCom();

		std::string *buffer;

	private:

		void	ilog(const std::string & name, const std::string & msg) const;

};

#endif

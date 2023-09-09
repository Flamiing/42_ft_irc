/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getCurrentTime.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:10:17 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/09 17:30:53 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

std::string getCurrentTime(void)
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
    long long microseconds = tv.tv_sec;
    std::stringstream ss;
    ss << microseconds;
    std::string currentTime = ss.str();
	return currentTime;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getCurrentTime.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:10:17 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/05 23:33:45 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include <sys/time.h>

/* void getTime(std::tm& timeStruct, char *timeString)
{
	std::istringstream ss(timeString);
    std::string month;
    ss >> timeStruct.tm_mday >> month >> timeStruct.tm_year >> timeStruct.tm_hour >> timeStruct.tm_min;
	
	timeStruct.tm_year -= 1900;
	
	std::string months[] =
	{
		"Jan","Feb","Mar","Apr","May", "Jun",
		"Jul","Aug","Sep","Oct","Nov","Dec"
	};

	size_t pos = 0;
	while (pos < 12)
	{
		if (month == months[pos])
		{
			timeStruct.tm_mon = pos;
			break ;
		}
		pos++;
	}
}

std::string getCurrentTime(void)
{
	std::time_t time;
    std::time(&time);
    char timeString[100];
    strftime(timeString, sizeof(timeString), "%e %b %Y at %H:%M", std::localtime(&time));
	
	std::tm timeStruct = {};
	getTime(timeStruct, timeString);
	
	time_t timeValue = std::mktime(&timeStruct);
	std::stringstream ssMicroseconds;
    ssMicroseconds << timeValue;
	std::string currentTime(ssMicroseconds.str());
	
	std::cout << "TIME: " << timeString << std::endl;
	std::cout << "TIME STR: " << currentTime << std::endl;
	return currentTime;
} */

std::string getCurrentTime(void)
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
    long long microseconds = tv.tv_sec;
    std::stringstream ss;
    ss << microseconds;
    std::string currentTime = ss.str();
	std::cout << "TIME: " << currentTime << std::endl;
	return currentTime;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalUtils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:37:45 by alaaouam          #+#    #+#             */
/*   Updated: 2023/08/30 19:15:05 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERALUTILS_CPP
# define GENERALUTILS_CPP

# include <iostream>
# include <sstream>
# include <string>
# include <vector>

bool parsePort(std::string& portStr, int& port);
std::vector<std::string> splitString(std::string& str, char delimiter);
std::string getMessage(const std::string& raw, const std::vector<std::string>& remove);
std::string trimSpaces(std::string& str);

#endif
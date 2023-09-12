/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyTemplates.tpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:02:45 by alaaouam          #+#    #+#             */
/*   Updated: 2023/09/12 10:16:10 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COPYTEMPLATES_TPP
# define COPYTEMPLATES_TPP

# include "Channel.hpp"

template<typename T>
void copyVector(std::vector<T>& dest, const std::vector<T>& src)
{
	size_t pos = 0;
	while (pos < src.size())
	{
		dest.push_back(src[pos]);
		pos++;
	}
}

template<typename KeyType, typename ValueType>
void copyMap(std::map<KeyType, ValueType>& dest, const std::map<KeyType, ValueType>& src)
{
	typename std::map<KeyType, ValueType>::const_iterator it = src.begin();
	while (it != src.end())
	{
		dest[it->first] = it->second;
		it++;
	}
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:10:59 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/12 17:13:45 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
  return ;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &inst)
{
  (void)inst;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& inst)
{
  (void)inst;
  return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
  return ;
}
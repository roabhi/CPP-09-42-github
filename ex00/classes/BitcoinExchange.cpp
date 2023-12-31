/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:10:59 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/18 14:44:06 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// ?  Cannonical

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

// ? Date parser

void	BitcoinExchange::parseDate(std::string date)
{
	for (int i = 0; i < (int)date.length(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (date[i] == '-')
				continue ;
			else
			{
				std::cout << date << " " << date[i] << std::endl;
				throw std::runtime_error("There's an error in a date.");
			}
		}
		else
		{
			if (date[i] >= '0' && date[i] <= '9')
				continue ;
			else
				throw std::runtime_error("There's an error in a date.");
		}
	}
}

// ? Paser for each line from the input file

void	BitcoinExchange::parseFileLine(std::string date, float price)
{
	bool	error = false;

	if (price < 0)
		throw std::out_of_range("Error: amount less than zero...");
	if (price > 1000)
		throw std::out_of_range("Error: amount bigger than 1000.");
	if (date.length() >= 10)
	{
		std::string	year = date.substr(0, 4);
		for (int i = 0; i < (int)year.length(); i++)
			if (!std::isdigit(year[i]))
				error = true;
		if (error == false && (std::stoi(year) > 2023 || std::stoi(year) < 2009))
			error = true;		
		std::string	month = date.substr(5, 2);
		for (int i = 0; i < (int)month.length(); i++)
			if (error == false && !std::isdigit(month[i]))
				error = true;
		if (error == false && std::stoi(month) > 12)
			error = true;
		std::string	day = date.substr(8, 2);
		for (int i = 0; i < (int)day.length(); i++)
			if (error == false && !std::isdigit(day[i]))
				error = true;
		if (error == false && std::stoi(day) > 31)
			error = true;
		if (error == false && std::stoi(day) < 2 && std::stoi(year) == 2009)
			error = true;
	}
	else
		error = true;
	if (error)
	{
		std::string	error = "Error: date ";
		error.append(date);
		error.append(" is invalid.");
		throw std::invalid_argument(error);
	}
}

// ? Open and process file form input

int	BitcoinExchange::processFile(std::string file_path)
{
	std::ifstream file(file_path);
	if (!file.is_open())
	{
		std::string error;
		error = "File ";
		error.append(file_path);
		error.append(" could not be opened.");
		throw std::runtime_error(error);
		return (1);
	}

	float	fprice = 0;
	std::string	line;
	int	lc = 0;
	while (std::getline(file, line))
	{
		std::istringstream linestream(line);
		std::string	date;
		std::string price;
		if (std::getline(linestream, date, '|') && std::getline(linestream, price))
		{
			try
			{
				date = date.substr(0,10);
				try
				{
					price = price.substr(1, price.length());
					for (int i = 0; i < (int)price.length(); i++)
						if (!std::isdigit(price[i]) && price[i] != '.' && price[i] != '-')
							throw std::invalid_argument("Error: invalid number");
					fprice = std::stof(price);
				}
				catch (std::exception &e)
				{
					throw std::invalid_argument("Error: invalid number.");
					return (1);
				}
				parseFileLine(date, fprice);
				std::map<std::string, float>::const_iterator it = BitcoinExchange::_data.lower_bound(date);
				if (it == BitcoinExchange::_data.begin() || (it != BitcoinExchange::_data.end() && it->first != date))
					--it;
				std::cout << date << " => " << fprice << " = " << it->second * fprice << std::endl;

			}
			catch (const std::exception& e)
			{
				if (lc > 0)
					std::cout << e.what() << std::endl;
			}
			lc++;
		}
		else
			std::cout << "Error: date " << line << " is invalid." << std::endl;
	}
	return (0);
}

// ? Initialize DB from .csv file

int BitcoinExchange::setDb()
{
  std::ifstream file(DB_PATH);
	if (!file.is_open())
		throw std::runtime_error("No se pudo abrir el archivo CSV.");
	int lc = 0;
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream linestream(line);
		std::string date;
		std::string price;

		if (std::getline(linestream, date, ',') && std::getline(linestream, price))
		{
			try
			{
				float fprice = std::stof(price);
				BitcoinExchange::parseDate(date);
				BitcoinExchange::_data[date] = fprice;
				

				// TODO printing formatted CSV

				// std::cout << " Date Price" << std::endl;
				// std::map<std::string, float>::iterator it = BitcoinExchange::_data.begin();



				// while (it != BitcoinExchange::_data.end())
				// {
				// 	// Accessing the key
				// 	std::string word = it->first;
				// 	// Accessing the price
				// 	float count = it->second;
				// 	std::cout << word << " :: " << count << std::endl;
				// 	// iterator incremented to point next item
				// 	it++;
				// }

				// TODO end of printing formatted CSV

			}
			catch (const std::exception& e)
			{
				if (lc > 0)
					return (1);
			}
			lc++;
		}
	}
	return (0);
}

// ? Entry point

void  BitcoinExchange::init(std::string file_path)
{

  if (BitcoinExchange::setDb())
    throw std::runtime_error("Error parsing dates from Database");
	if (BitcoinExchange::processFile(file_path))
		throw std::runtime_error("Error processing input file. Check your prices");
}

// ?  Static reference for private map container

std::map<std::string, float> BitcoinExchange::_data; 
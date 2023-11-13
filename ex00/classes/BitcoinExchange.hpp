/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:59:33 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/13 17:11:37 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iomanip>
# include <map>
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <climits>
# include <cfloat>

# define DB_PATH "./data/data.csv"

class BitcoinExchange {

  public:
    
    static void   init(std::string file_path);


  private:
    // ? Cannnical - THIS IS A STATIC CLASS, constructors are private
    BitcoinExchange(void);    
    BitcoinExchange(const BitcoinExchange &inst);
    BitcoinExchange &operator=(const BitcoinExchange& inst);
    ~BitcoinExchange(void);

    // ? Member vars
    static std::map<std::string, float>  _data;

    // ? Member funcs
    static int   setDb(void);
    static void	parseDate(std::string date);
    static int processFile(std::string file_path);
    static void	parseFileLine(std::string date, float value);

    



};

#endif
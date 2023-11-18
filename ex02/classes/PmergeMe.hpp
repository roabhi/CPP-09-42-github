/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:12:26 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/18 17:00:05 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <sstream>
# include <deque>
# include <vector>
# include <algorithm>
# include <limits>
# include <ctime>

class PmergeMe {

  public:
    static void init(char **input);

  private:

    // ? Cannonical
    PmergeMe(void);
    PmergeMe(const PmergeMe &inst);
    PmergeMe& operator=(const PmergeMe &inst);
    ~PmergeMe(void);

    // ? containers

    static std::vector< int >	_vec;
	  static std::deque< int >	_dque;

    // ? Member functions UTILS

    static void		    	checkInput(char **input);
    static void		    	printContainer( std::string msg, std::vector< int > vec );
    static void         printTimes( int range, std::string container_name, double timeDiff );
    static bool         isNumPos( std::string num, std::string& error );
    static bool         isNumInt( std::string num, std::string& error );
    static std::string  intToStr(int num);

    // ? Member functions SORTERS

    static void         sortVec(unsigned int start, unsigned int end );
    static void         sortMergeVec( unsigned int start, unsigned int mid, unsigned int end );
    static void         sortInsertVec( unsigned int start, unsigned int end );

    static void         sortDque(unsigned int start, unsigned int end);
    static void         sortMergeDque(unsigned int start, unsigned int mid, unsigned int end);
    static void         sortInsertDque(unsigned int start, unsigned int end);
};

#endif
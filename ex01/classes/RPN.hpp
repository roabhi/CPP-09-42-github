/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:46:32 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/18 14:53:40 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <sstream>

class RPN {
  public:
  
    static int init(std::string input);

  private:
  
    // ? Cannonical - THIS IS A STATIC CLASS
    RPN(void);
    RPN(const RPN &inst);
    RPN &operator=(const RPN& inst);
    ~RPN(void);

    //? Member vars
    static std::stack<int>  _stack;

    // ? Member funcs

    static void parseData(std::string);
    static int  calc(char c);
    
};

#endif
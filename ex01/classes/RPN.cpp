/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:09:22 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/13 19:13:40 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
  return ;
}

RPN::RPN(const RPN &inst)
{
  (void)inst;
}

RPN &RPN::operator=(const RPN& inst)
{
  (void)inst;
  return (*this);
}

RPN::~RPN(void)
{
  return ;
}

void RPN::init(std::string input)
{
  std::cout << "string from RPN is " << input << std::endl;
}


std::stack<int>  RPN::_stack;
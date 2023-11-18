/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:09:22 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/18 15:02:54 by rabril-h         ###   ########.fr       */
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

// ? Calc values 

int RPN::calc(char c)
{

  int f = RPN::_stack.top();
  RPN::_stack.pop();
  int s = RPN::_stack.top();
  RPN::_stack.pop();

  std::string sign[4] = {"-","+","/","*"};

  int count = 0;
  while (sign[count][0] != c)
    count++;
  switch (count) 
  {
    case 0:
      return (s - f);
    case 1:
      return (s + f);
    case 2:
      if (f == 0)
        throw std::invalid_argument("Not a valid input");
      return (s / f);
    case 3:
      double safe = (static_cast<double>(s) * static_cast<double>(f));
      if (safe > INT_MAX || safe < INT_MIN)
        throw std::invalid_argument("Result number is too big or too small!");
      return (s * f);
  }
  return (0);
}

// ? Argv parser as Reverse Polish Notation rules (1 1 +) is equal 2 not (1 + 1)

void  RPN::parseData(std::string input)
{
  unsigned int c = 0;

  while (input[c])
  {
    if (input[c] >= '0' && input[c] <= '9')
    {
      if ((c > 0 && input[c - 1] == ' ') || c == 0)
        RPN::_stack.push(input[c] - '0');
      else
        throw std::invalid_argument("Not a valid input");
    }
    else if (input[c] == '-' || input[c] == '+' || input[c] == '*' || input[c] == '/')
    {
      if (c > 0 && input[c - 1] == ' ')
      {
        if (RPN::_stack.size() > 1)
        {
          RPN::_stack.push(RPN::calc(input[c])); // ? send to calc here so stack only has one number at the end of calculation
        }
        else
        {
          throw std::invalid_argument("Not a valid input");
        }
      }
      else
        throw std::invalid_argument("Not a valid input");
    }
    else if (input[c] != ' ')
      throw std::invalid_argument("Not a valid input");
    c++;
  }
}

// ? Entry point

int RPN::init(std::string input)
{
  RPN::parseData(input);
  
  if (RPN::_stack.size() == 1)
    return (RPN::_stack.top());
  throw std::invalid_argument("Not a valid input");
}

// ? Static reference for private container

std::stack<int>  RPN::_stack;
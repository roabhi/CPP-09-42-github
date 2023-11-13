/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:38:43 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/13 19:16:33 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./classes/RPN.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cout << "Please provide an operation between quotesto perform Usage: ./RPN \"....\" " << std::endl;
    return (1);
  }

  try
  {
    RPN::init(argv[1]);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  } 
  
  return (0);
}
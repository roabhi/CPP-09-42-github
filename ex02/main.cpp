/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:04:25 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/18 16:49:14 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./classes/PmergeMe.hpp"

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cerr << "Please provide arguments. Usage: ./PmergeMe <number1, number2, number3, ... numberN>" << std::endl;
    return (1);
  }

  try
  {
    PmergeMe::init(&argv[1]);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  
  return (0);
}
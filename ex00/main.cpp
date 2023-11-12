/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:31:01 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/12 17:17:34 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv)
{
  
  
  if (argc != 2)
  {
    std::cout << "Please provide one file as argument. Usage: ./btc <path_to_input_file>" << std::endl;
    return (1);
  }

  try
  {
    std::cout << argv[1] << std::endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  



  return (0);
}
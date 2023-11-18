/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:16:50 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/18 16:57:14 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// * Cannonical

PmergeMe::PmergeMe(void)
{
  return ;
}

PmergeMe::PmergeMe(const PmergeMe &inst)
{
  (void)inst;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &inst)
{
  (void)inst;
  return (*this);
}

PmergeMe::~PmergeMe(void)
{
  return ;
}

void	PmergeMe::printContainer( std::string msg, std::vector< int > vec )
{
	std::cout << msg << ":\t";
	for ( std::vector< int >::iterator it = vec.begin(); it != vec.end(); it++ )
	{
		std::cout << *it;
		if ( it + 1 != vec.end() )
			std::cout << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printTimes( int range, std::string container_name, double timeDiff )
{
	std::cout << std::fixed;
	std::cout << "Time to process a range of " << range;
	std::cout << " elements with std::" << container_name;
	std::cout << " : " << timeDiff << " us" << std::endl;
}


bool	PmergeMe::isNumPos( std::string num, std::string& error )
{
	size_t	i;
	bool	negative;

	negative = num[ 0 ] == '-' ? true : false;
	i = num[ 0 ] == '-' || num[ 0 ] == '+' ? 1 : 0;
	for ( ; i < num.length(); i++ )
	{
		if ( std::isdigit( num[ i ] ) == false )
		{
			error = "Error: Not a number: ";
			return ( false );
		}
	}
	if ( negative == true )
	{
		error = "Error: Do not use negative values: ";
		return ( false );
	}
	return ( true );
}

std::string PmergeMe::intToStr(int num)
{
  std::stringstream ss;
  ss << num;
  return ss.str();
}

bool	PmergeMe::isNumInt( std::string num, std::string& error )
{
	size_t		len;
	std::string	integerMax;

	if ( num[ 0 ] == '+' )
		num.erase( 0, 1 );
	len = num.length();
	if ( len == 0 )
	{
		error = "Error: please do not place empty values: ";
		return ( false );
	}
	integerMax = intToStr( INT_MAX );
	if ( len > integerMax.length() \
		|| ( len == integerMax.length() \
			&& integerMax.compare( num ) < 0 ) )
	{
		error = "Error: Number bigger than int: ";
		return ( false );
	}
	return ( true );
}

void	PmergeMe::checkInput(char **input)
{
	std::string	error;

	error = "Error: ";
	for ( int i = 0; input[ i ] != NULL; i++ )
	{
		if ( !isNumPos( input[ i ], error ) )
			throw std::invalid_argument( error + std::string( input[ i ] ) );
		if ( !isNumInt( input[ i ], error ) )
			throw std::invalid_argument( error + std::string( input[ i ] ) );
		// ? check param
		// std::cout << std::atoi(input [i]) << std::endl;
		// ? We do not tolerate duplicate numebers as stated in the subject as left to my discretion
		if ( std::find< std::vector< int >::iterator, int >( PmergeMe::_vec.begin(), PmergeMe::_vec.end(), std::atoi( input[ i ] ) ) != PmergeMe::_vec.end() )
			throw std::invalid_argument( "Error: Duplicate number are not allowed : " + std::string( input[ i ] ) );
		PmergeMe::_vec.push_back( std::atoi( input[ i ] ) );
		PmergeMe::_dque.push_back( std::atoi( input[ i ] ) );
	}
}


// * Sorting Funcs 

// ? Vector

void	PmergeMe::sortMergeVec( unsigned int start, unsigned int mid, unsigned int end )
{
	unsigned int		limits[ 2 ];
	unsigned int		idx[ 2 ];
	std::vector< int >	sides[ 2 ];
	limits[ 0 ] = mid - start + 1;
	limits[ 1 ] = end - mid;

	sides[ 0 ].insert( sides[ 0 ].begin(), PmergeMe::_vec.begin() + start, PmergeMe::_vec.begin() + mid + 1 );
	sides[ 1 ].insert( sides[ 1 ].begin(), PmergeMe::_vec.begin() + mid + 1, PmergeMe::_vec.begin() + end + 1 );
	idx[ 0 ] = 0;
	idx[ 1 ] = 0;
	for ( unsigned int i = start; i - start < end - start + 1; i++ )
	{
		if ( idx[ 0 ] == limits[ 0 ] )
			PmergeMe::_vec[ i ] = sides[ 1 ][ idx[ 1 ]++ ];
		else if ( idx[ 1 ] == limits[ 1 ] )
			PmergeMe::_vec[ i ] = sides[ 0 ][ idx[ 0 ]++ ];
		else if ( sides[ 0 ][ idx[ 0 ] ] < sides[ 1 ][ idx[ 1 ] ] )
			PmergeMe::_vec[ i ] = sides[ 0 ][ idx[ 0 ]++ ];
		else
			PmergeMe::_vec[ i ] = sides[ 1 ][ idx[ 1 ]++ ];
	}
}

void	PmergeMe::sortInsertVec( unsigned int start, unsigned int end )
{
	unsigned int	j;
	int				tmp;

	for ( unsigned int i = start; i < end; i++ )
	{
		j = i + 1;
		tmp = PmergeMe::_vec[ j ];
		for ( ; j > start && PmergeMe::_vec[ j - 1 ] > tmp ; j-- )
			PmergeMe::_vec[ j ] = PmergeMe::_vec[ j - 1 ];
		PmergeMe::_vec[ j ] = tmp;
	}
}

void	PmergeMe::sortVec(unsigned int start, unsigned int end )
{
	int	mid;

	if ( end - start > 5 ) // ? Take five as size for splitting groups with a middle value / chunks
	{
		mid = ( start + end ) / 2;
		sortVec( start, mid );
		sortVec( mid + 1, end );
		sortMergeVec( start, mid, end );
	}
	else
		sortInsertVec( start, end );
}

// ? Dque

void PmergeMe::sortInsertDque(unsigned int start, unsigned int end)
{
	unsigned int	j;
	int				tmp;

	for ( unsigned int i = start; i < end; i++ )
	{
		j = i + 1;
		tmp = PmergeMe::_dque[ j ];
		for ( ; j > start && PmergeMe::_dque[ j - 1 ] > tmp ; j-- )
			PmergeMe::_dque[ j ] = PmergeMe::_dque[ j - 1 ];
		PmergeMe::_dque[ j ] = tmp;
	}
}

void PmergeMe::sortMergeDque(unsigned int start, unsigned int mid, unsigned int end)
{
	unsigned int		limits[ 2 ];
	unsigned int		idx[ 2 ];
	std::deque< int >	sides[ 2 ];
	limits[ 0 ] = mid - start + 1;
	limits[ 1 ] = end - mid;

	sides[ 0 ].insert( sides[ 0 ].begin(), PmergeMe::_dque.begin() + start, PmergeMe::_dque.begin() + mid + 1 );
	sides[ 1 ].insert( sides[ 1 ].begin(), PmergeMe::_dque.begin() + mid + 1, PmergeMe::_dque.begin() + end + 1 );
	idx[ 0 ] = 0;
	idx[ 1 ] = 0;
	for ( unsigned int i = start; i - start < end - start + 1; i++ )
	{
		if ( idx[ 0 ] == limits[ 0 ] )
			PmergeMe::_dque[ i ] = sides[ 1 ][ idx[ 1 ]++ ];
		else if ( idx[ 1 ] == limits[ 1 ] )
			PmergeMe::_dque[ i ] = sides[ 0 ][ idx[ 0 ]++ ];
		else if ( sides[ 0 ][ idx[ 0 ] ] < sides[ 1 ][ idx[ 1 ] ] )
			PmergeMe::_dque[ i ] = sides[ 0 ][ idx[ 0 ]++ ];
		else
			PmergeMe::_dque[ i ] = sides[ 1 ][ idx[ 1 ]++ ];
	}
}

void	PmergeMe::sortDque(unsigned int start, unsigned int end)
{
	int	mid;

	if ( end - start > 5 )
	{
		mid = ( start + end ) / 2;
		sortDque( start, mid );
		sortDque( mid + 1, end );
		sortMergeDque( start, mid, end );
	}
	else
		sortInsertDque( start, end );
}


// * Entry point
void PmergeMe::init(char **input)
{ 
  std::clock_t		vecTime[ 2 ];
	std::clock_t		dqueTime[ 2 ];  
  
  checkInput( input);
  printContainer("Before", PmergeMe::_vec);

	// ? sorting and insertion for vector -  take into account sorting and inserting times
  vecTime[ 0 ] = std::clock();
  sortVec(0, PmergeMe::_vec.size() - 1);
  vecTime[ 1 ] = std::clock();
	// ? sorting and insertion for dque - take into account sroting and inserting times
	dqueTime[ 0 ] = std::clock();
	sortDque(0, PmergeMe::_dque.size() - 1);
	dqueTime[ 1 ] = std::clock();
	printContainer("After", PmergeMe::_vec);


	// ? print result for vector
  printTimes( PmergeMe::_vec.size(), "vector", ( static_cast< double >( vecTime[ 1 ] - vecTime[ 0 ] ) / CLOCKS_PER_SEC ) * 1000000 );
	// ? print result for dque
	printTimes( PmergeMe::_dque.size(), "deque", ( static_cast< double >( dqueTime[ 1 ] - dqueTime[ 0 ] ) / CLOCKS_PER_SEC ) * 1000000 );

}

std::vector<int>  PmergeMe::_vec;
std::deque<int> PmergeMe::_dque;
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:16:50 by rabril-h          #+#    #+#             */
/*   Updated: 2023/11/16 22:02:42 by rabril-h         ###   ########.fr       */
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

// * Utils funcs
template < typename T >
bool	PmergeMe::isSorted( typename T::iterator begin, typename T::iterator end )
{
	typename T::value_type	last;

	for ( typename T::iterator it = begin; it != end; it++ )
	{
		if ( it != begin &&  *it < last )
			return ( false );
		last = *it;
	}
	return ( true );
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
		error = "Error Not a positive number: ";
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
		error = "Error: empty string is not a valid number: ";
		return ( false );
	}
	integerMax = intToStr( INT_MAX );
	if ( len > integerMax.length() \
		|| ( len == integerMax.length() \
			&& integerMax.compare( num ) < 0 ) )
	{
		error = "Error: Not an integer -> [ overflow ]: ";
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
		if ( std::find< std::vector< int >::iterator, int >( PmergeMe::_vec.begin(), PmergeMe::_vec.end(), std::atoi( input[ i ] ) ) != PmergeMe::_vec.end() )
			throw std::invalid_argument( "Error: Duplicate number is invalid => " + std::string( input[ i ] ) );
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

	if ( end - start > 5 )
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

	// ? sorting and insertion for vector
  vecTime[ 0 ] = std::clock();
  sortVec(0, PmergeMe::_vec.size() - 1);
  vecTime[ 1 ] = std::clock();
	// ? sorting and insertion for dque
	dqueTime[ 0 ] = std::clock();
	sortDque(0, PmergeMe::_dque.size() - 1);
	dqueTime[ 1 ] = std::clock();
	printContainer("After", PmergeMe::_vec);


	// ? print result for vector
  printTimes( PmergeMe::_vec.size(), "vector", ( static_cast< double >( vecTime[ 1 ] - vecTime[ 0 ] ) / CLOCKS_PER_SEC ) * 1000000 );
	// ? print result for dque
	printTimes( PmergeMe::_dque.size(), "deque", ( static_cast< double >( dqueTime[ 1 ] - dqueTime[ 0 ] ) / CLOCKS_PER_SEC ) * 1000000 );

	// ? final checks

	// if ( PmergeMe::isSorted< std::vector< int > >( PmergeMe::_vec.begin(), PmergeMe::_vec.end() ) == false )
	// 	throw std::runtime_error( "\033[1;91mVector Is not sorted\033[1;97m" );
	// std::cout << "\033[1;92mVector Is sorted\033[1;97m" << std::endl;
	// if ( PmergeMe::isSorted< std::deque< int > >( PmergeMe::_dque.begin(), PmergeMe::_dque.end() ) == false )
	// 	throw std::runtime_error( "\033[1;91mDeque Is not sorted\033[1;97m" );
	// std::cout << "\033[1;92mDeque Is sorted\033[1;97m" << std::endl;

}

std::vector<int>  PmergeMe::_vec;
std::deque<int> PmergeMe::_dque;
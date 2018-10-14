#pragma once
#include "tuple0.hpp"
#include "tupleget.hpp"


// basic case
/**
 * \brief empty tuples are always equivalent
 * \param t1 
 * \param t2 
 * \return 
 */
inline bool operator==(Tuple<> const& t1, Tuple<> const& t2)
{
	return true;
}


template<
	typename Head1, typename...Tail1,
	typename Head2, typename...Tail2,
	typename = std::enable_if_t<sizeof...(Tail1)==sizeof...(Tail2)>
>
inline bool operator==( Tuple<Head1, Tail1...> const& t1, Tuple<Head2, Tail2...> const& t2)
{
	return t1.getHead() == t2.getHead() && t1.getTail() == t2.getTail();
}
	

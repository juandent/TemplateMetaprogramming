#pragma once
#include "tuple0.hpp"


// recursive step
template<typename ...Types>
void printTuple( std::ostream& strm, Tuple<Types...> const& t, bool isFirst=false)
{
	if (isFirst)
	{
		strm << "(";
	}
	else
	{
		strm << ", ";
	}
	strm << t.getHead();
	printTuple(strm, t.getTail());
}

// basic step
template<>
void printTuple( std::ostream& strm, Tuple<> const& t, bool isFirst)
{
	strm << ")";
}





template<typename...Types>
std::ostream& operator<<( std::ostream& strm, Tuple<Types...> const& t)
{
	printTuple(strm, t, true);
	return strm;
}



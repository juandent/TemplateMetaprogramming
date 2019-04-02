#pragma once

#include "tupletypelist.hpp"
#include "pushback.hpp"

inline Tuple<> reverse(Tuple<> const& t)
{
	return t;
}

template<typename Head, typename ...Tail>
Reverse<Tuple<Head, Tail...>> reverse( Tuple<Head,Tail...> const& t)
{
	return pushBack(reverse(t.getTail()), t.getHead());
}


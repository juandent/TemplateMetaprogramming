#pragma once
#include "tuple0.hpp"

template<typename V>
Tuple<> popFront( Tuple<V> const& tuple)
{
	return Tuple<>();
}


template<typename Head, typename...Tail>
Tuple<Tail...> popFront( Tuple<Head, Tail...> const& tuple)
{
	return Tuple<Tail...>(tuple.getTail());
}

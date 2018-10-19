#pragma once
#include "tuple0.hpp"
#include "tupletypelist.hpp"


template<typename V>
Tuple<V> pushBack(Tuple<> const&, V value)
{
	return Tuple<V>(value);
}

#if 1
template<typename Head, typename...Tail, typename V>
typename PushBackT < Tuple<Head, Tail...>, V>::Type
//auto 
pushBack(Tuple<Head, Tail...> const& tuple, V value)
{
	return typename PushBackT <Tuple<Head, Tail...>, V>::Type(tuple.getHead(), pushBack(tuple.getTail(), value));
}

#else
template<typename Head, typename...Tail, typename V>
Tuple<Head, Tail...,V>
pushBack(Tuple<Head, Tail...> const& tuple, V value)
{
	return Tuple<Head, Tail..., V>(tuple.getHead(), pushBack(tuple.getTail(), value));
}

#endif

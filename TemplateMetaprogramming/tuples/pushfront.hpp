#pragma once


#include "tupletypelist.hpp"


template<typename...Types, typename Element>
typename PushFrontT<Tuple<Types...>, Element>::Type
pushFront(Tuple<Types...> const& tuple, Element const& value )
{
	return typename PushFrontT<Tuple<Types...>, Element>::Type (value,tuple);
}

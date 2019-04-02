#pragma once

#include "tupletypelist.hpp"
#include "reverse.hpp"
#include "popfront.hpp"


template<typename...Types>
PopBack<Tuple<Types...>>
popBack( Tuple<Types...> const& t)
{
	return reverse(popFront(reverse(t)));
}

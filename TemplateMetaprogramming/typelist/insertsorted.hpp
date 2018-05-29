#pragma once


#include "insertionsort.hpp"
#include "..\traits\IfThenElse.hpp"
#include "typelistPushFront.hpp"
#include "Identity.hpp"

//template<typename List, typename Element, template<typename T, typename U> class Compare, bool = IsEmpty<List>::value>
//class InsertSortedT;

// recursive case
template<typename List, typename Element, template<typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, false>
{
	using NewTail = typename IfThenElseT< Compare<Element, Front<List>>::value, IdentityT<List>,
		InsertSortedT<PopFront<List>, Element, Compare>>::Type;

	using NewHead = IfThenElse< Compare<Element, Front<List>>::value, Element, Front<List>>;
public:
	using Type = PushFront< NewTail, NewHead>;
};



// basis case
template<typename List, typename Element, template<typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, true>
	: public PushFrontT<List, Element>
{};


#if 0
{
public:
	using Type = Typelist<Element>;
};
#endif

template<typename List, typename Element, template<typename T, typename U> class Compare>
using InsertSorted = typename InsertSortedT<List, Element, Compare>::Type;

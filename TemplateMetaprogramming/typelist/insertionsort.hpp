#pragma once

#ifndef CONSCELL
#include "IsEmpty.hpp"
#include "typelistPopFront.hpp"
#include "typelistFront.hpp"
#else
#include "../typelistConsIsEmpty.hpp"
#include "../typelistConsPopFront.hpp"
#include "../typelistConsFront.hpp"
#endif

template<typename List,
	template<typename T, typename U> class Compare,
	bool = IsEmpty<List>::value>
	class InsertionSortT;

template<typename List, typename Element, template<typename T, typename U> class Compare, bool isEmpty = IsEmpty<List>::value>
class InsertSortedT;


template<typename List, template<typename T, typename U> class Compare>
using InsertionSort = typename InsertionSortT<List, Compare>::Type;

// insert first element into sorted list
template<typename List, template<typename T, typename U> class Compare>
class InsertionSortT<List, Compare,false>
	: public InsertSortedT< InsertionSortT<PopFront<List>, Compare>, Front<List>, Compare>
{};


// basis case (empty list is sorted)
template<typename List, template<typename T, typename U> class Compare>
class InsertionSortT<List, Compare, true>
{
public:
	using Type = List;
	using Head = Nil;
	using Tail = Nil;
};


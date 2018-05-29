#pragma once

#include "IsEmpty.hpp"
#include "typelistPopFront.hpp"
#include "typelistFront.hpp"


template<typename List, template<typename X, typename Y> class F, typename I,
	bool = IsEmpty<List>::value>
	class AccumulateT;

template<typename List, template<typename X, typename Y> class F, typename I>
	class AccumulateT<List, F, I, false>
	: public AccumulateT < PopFront<List>, F, typename F<I, Front<List>>::Type>
{};

template<typename List, template<typename X, typename Y> class F, typename I>
	class AccumulateT<List, F, I, true>
{
public:
	using Type = I;
};


template<typename List, template<typename X, typename Y> class F, typename I>
	using Accumulate = typename AccumulateT<List, F, I>::Type;

/////////////////////////////////////////////////
// implement Reverse with Accumulate
// F = PushFront, I = Typelist<>

#include "typelistPushFront.hpp"
#include "typelistPushBack.hpp"

template< typename List>
using Reverse_via_accumulate = Accumulate<List, PushFrontT, Typelist<>>;



	



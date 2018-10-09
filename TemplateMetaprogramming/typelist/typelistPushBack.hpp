#pragma once

#include "Typelist.hpp"

template<typename List, typename NewElement>
struct PushBackT;

template<typename...Elements, typename NewElement>
struct PushBackT< Typelist<Elements...>, NewElement>
{
public:
	using Type = Typelist<Elements..., NewElement>;
};

template<typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;


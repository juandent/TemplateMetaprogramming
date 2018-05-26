#pragma once

#include "typelistReverse.hpp"
#include "typelistPopFront.hpp"

// reverse list
// popfront
// reverse list again


template<typename List>
class PopBackT
{
public:
	using Type = Reverse<PopFront<Reverse<List>>>;
};

template<typename List>
using PopBack = typename PopBackT<List>::Type;


#pragma once

#include "IsEmpty.hpp"
#include "typelistFront.hpp"
#include "typelistPushBack.hpp"
#include "typelistPopfront.hpp"


template<typename List, bool Empty = IsEmpty<List>::value>
class ReverseT;

template<typename List>
using Reverse = typename ReverseT<List>::Type;

template<typename List>
class ReverseT<List, false> : public PushBackT<Reverse<PopFront<List>>, Front<List>>
{};

template<typename List>
class ReverseT<List, true>
{
public:
	using Type = List;
};


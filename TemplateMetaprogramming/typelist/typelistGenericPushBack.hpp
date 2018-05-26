#pragma once

#include "Typelist.hpp"
#include "IsEmpty.hpp"
#include "typelistFront.hpp"
#include "typelistPopFront.hpp"
#include "typelistPushFront.hpp"


template<typename List, typename NewElement, bool Empty = IsEmpty<List>::value>
class PushBackRecT;

template<typename List, typename NewElement>
class PushBackRecT<List, NewElement, false>
{
public:
	using Head = Front<List>;
	using Tail = PopFront<List>;
	using NewTail = typename PushBackRecT<Tail, NewElement>::Type;
public:
	using Type = PushFront<Head, NewTail>;
};


template<typename List, typename NewElement>
class PushBackRecT<List, NewElement, true>
{
public:
	using Type = PushFront<List, NewElement>;
};


template<typename List, typename NewElement>
using PushBackRec = typename PushBackRecT<List, NewElement>::Type;


#pragma once


// PopFront:

template<typename List>
struct PopFrontT;

template<typename Head, typename...Tail>
struct PopFrontT < Typelist<Head, Tail...>>
{
public:
	using Type = Typelist<Tail...>;
};

template<typename List>
using PopFront = typename PopFrontT<List>::Type;

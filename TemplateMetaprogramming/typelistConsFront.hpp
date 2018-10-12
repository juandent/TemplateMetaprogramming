#pragma once

template<typename List>
struct FrontT
{
	using Type = typename List::Head;
};

template<>
struct FrontT<Nil>
{
	using Type = Nil;
	using Head = Nil;
};


template<typename List>
using Front = typename FrontT<List>::Type;


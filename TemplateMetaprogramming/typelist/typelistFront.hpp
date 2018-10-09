#pragma once

// Front:

template<typename List>
struct FrontT;

template<typename Head, typename...Tail>
struct FrontT < Typelist<Head, Tail...>>
{
public:
	using Type = Head;
};

template<typename List>
using Front = typename FrontT<List>::Type;


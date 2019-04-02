#pragma once
#include "tuple0.hpp"


#if 1
  template<typename ...Types>
struct IsEmpty
{
	constexpr static bool value = false;
};
#endif


template<>
struct IsEmpty<Tuple<>>
{
	constexpr static bool value = true;
};

template<typename Head, typename...Tail>
struct FrontT
{
	using Type = Head;
};

template<typename List, typename NewElement>
struct PushFrontT;

template<typename ...Types, typename NewElement>
struct PushFrontT<Tuple<Types...>, NewElement>
{
	using Type = Tuple<NewElement, Types...>;
};

template<typename ...Types>
struct PopFrontT;

template<typename Head, typename ...Tail>
struct PopFrontT<Tuple<Head,Tail...>>
{
	using Type = Tuple<Tail...>;
};


template<typename List, typename NewElement>
struct PushBackT;


template<typename ...Types, typename NewElement>
struct PushBackT<Tuple<Types...>, NewElement>
{
	using Type = Tuple<Types..., NewElement>;
};

template<typename List, bool Empty = IsEmpty<List>::value>
struct ReverseT;

template<typename List>
using Reverse = typename ReverseT<List>::Type;

template<typename ...Types>
using PopFront = typename PopFrontT<Types...>::Type;

template<typename...Types>
using Front = typename FrontT<Types...>::Type;


template<typename List>
struct FrenteT;

template<typename Head, typename...Tail>
struct FrenteT<Tuple<Head, Tail...>>
{
	using Type = Head;
};

template<typename List>
struct ReverseT<List, false>
	: PushBackT<Reverse<PopFront<List>>, typename FrenteT<List>::Type>
{};

template<typename List>
struct ReverseT<List, true>
{
	using Type = List;
};

template<typename List>
class PopBackT
{
public:
	using Type = Reverse<PopFront<Reverse<List>>>;
};

template<typename List>
using PopBack = typename PopBackT<List>::Type;




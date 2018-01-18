#pragma once

struct nil_t {};

template<typename>
struct head
{
	using type = nil_t;
};

template<template<typename...> class Seq, typename First, typename ...Rest>
struct head<Seq<First, Rest...>>
{
	using type = First;			// return type: an element of the seq
};

template<typename Seq>
using head_t = typename head<Seq>::type;

template<typename>
struct tail
{
	using type = nil_t;
};
template<template<typename...> class Seq, typename First, typename ...Rest>
struct tail<Seq<First, Rest...>>
{
	using type = Seq<Rest...>;	// return type: a sequence skipping the head element
};
template<typename Seq>
using tail_t = typename tail<Seq>::type;


/////////////////
// vector
template<typename...TypeElements>
struct vector
{};


//////////////////
// get_by_pos

template<size_t N, typename>
struct get_by_pos
{
	using type = nil_t;
};

template<size_t N, template<typename...> typename Seq, typename Head, typename...Tail>
struct get_by_pos<N, Seq<Head, Tail...>>
{
	using type = typename get_by_pos<N - 1, Seq<Tail...>>::type;
};

template<template<typename...> typename Seq, typename Head, typename...Tail>
struct get_by_pos<0, Seq<Head, Tail...>>
{
	using type = Head;
};


using aVector = vector<int, char>;
using type_1 = get_by_pos<1, aVector>::type;


//////////////////////////
// push_back_external

template<typename Elem, typename Seq>
struct push_back_external
{
	//using type = nil_t;
};

template<typename Elem, template<typename...> typename Seq>
struct push_back_external<Seq<>, Elem>
{
	using type = vector<Elem>;
};


template<typename Elem, template<typename...> typename Seq, typename Head, typename...Tail>
struct push_back_external<Seq<Head, Tail...>, Elem>
{
	using type = vector<Head, Tail..., Elem>;
};

using pushed_back = push_back_external<vector<int>, long double>::type;

//////////////////////////
// push_front_external

template<typename Seq, typename Elem>
struct push_front_external
{
	//using type = nil_t;
};

template<typename Elem, template<typename...> typename Seq>
struct push_front_external<Seq<>, Elem>
{
	using type = vector<Elem>;
};


template<typename Elem, template<typename...> typename Seq, typename Head, typename...Tail>
struct push_front_external<Seq<Head, Tail...>, Elem>
{
	using type = vector<Elem, Head, Tail...>;
};

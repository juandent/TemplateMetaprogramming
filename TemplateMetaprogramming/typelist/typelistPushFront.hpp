#pragma once

// PushFront:
template<typename List, typename NewElement>
struct PushFrontT;

template<typename...Elements, typename NewElement>
struct PushFrontT<  Typelist<Elements...>, NewElement>
{
public:
	using Type = Typelist< NewElement, Elements...>;
};

template<typename...Elements, typename NewElement>
struct PushFrontT<  NewElement, Typelist<Elements...>>
{
public:
	using Type = Typelist< NewElement, Elements...>;
};


template<typename List, typename NewElement>
using PushFront = typename PushFrontT<List, NewElement>::Type;

#pragma once

// PushFront:
template<typename List, typename NewElement>
class PushFrontT;

template<typename...Elements, typename NewElement>
class PushFrontT<  Typelist<Elements...>, NewElement>
{
public:
	using Type = Typelist< NewElement, Elements...>;
};

template<typename...Elements, typename NewElement>
class PushFrontT<  NewElement, Typelist<Elements...>>
{
public:
	using Type = Typelist< NewElement, Elements...>;
};


template<typename List, typename NewElement>
using PushFront = typename PushFrontT<List, NewElement>::Type;

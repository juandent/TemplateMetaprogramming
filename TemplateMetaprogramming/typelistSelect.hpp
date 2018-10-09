#pragma once
#include "typelist/Valuelist.hpp"
#include "typelist/typelistNthElement.hpp"


template<typename Types, typename Indices>
class SelectT;


template<typename Types, unsigned...Indices>
class SelectT<Types, ValueList<unsigned, Indices...>>
{
public:
	using Type = Typelist<NthElement<Types, Indices>...>;
};

template<typename Types, typename Indices>
using Select = typename SelectT<Types, Indices>::Type;


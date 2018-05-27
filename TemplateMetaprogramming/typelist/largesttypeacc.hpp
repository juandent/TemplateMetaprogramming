#pragma once

#include "largerType.hpp"
#include "accumulate.hpp"

template<typename Typelist, bool = IsEmpty<Typelist>::value>
class LargestTypeAccOkNullT;

template<typename Typelist>
class LargestTypeAccOkNullT<Typelist, false>
	: public AccumulateT<PopFront<Typelist>, LargerTypeT, Front<Typelist>>
{};

template<typename Typelist>
class LargestTypeAccOkNullT<Typelist, true>
{};


template<typename Typelist>
using LargestTypeAccOkNull = typename LargestTypeAccOkNullT<Typelist>::Type;


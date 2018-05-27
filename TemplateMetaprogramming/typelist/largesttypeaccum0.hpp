#pragma once

#include "largerType.hpp"
#include "accumulate.hpp"
#include "typelistPopFront.hpp"
#include "typelistFront.hpp"


template<typename List>
class LargestTypeAccT : public AccumulateT<PopFront<List>, LargerTypeT, Front<List>>
{};

template<typename List>
using LargestTypeAcc = typename LargestTypeAccT<List>::Type;



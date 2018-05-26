#pragma once

// NthElement

template<typename List, unsigned N>
class NthElementT : public NthElementT< PopFront< List>, N - 1>
{};

template<typename List>
class NthElementT<List, 0> : public FrontT<List>
{};

template<typename List, unsigned N>
using NthElement = typename NthElementT<List, N>::Type;


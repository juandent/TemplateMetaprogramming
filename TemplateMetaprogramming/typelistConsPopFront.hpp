#pragma once

template<typename List>
struct PopFrontT
{
	using Type = typename List::Tail;
};

template<typename List>
using PopFront = typename PopFrontT<List>::Type;


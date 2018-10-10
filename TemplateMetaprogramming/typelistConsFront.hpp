#pragma once

template<typename List>
struct FrontT
{
	using Type = typename List::Head;
};

template<typename List>
using Front = typename FrontT<List>::Type;


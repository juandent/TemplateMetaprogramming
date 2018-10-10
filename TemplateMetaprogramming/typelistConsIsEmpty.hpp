#pragma once
#include "typelistCons.hpp"

template<typename List>
struct IsEmpty
{
	static constexpr bool value = false;
};

template<>
struct IsEmpty<Nil>
{
	static constexpr bool value = true;
};


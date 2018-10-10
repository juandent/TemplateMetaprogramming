#include "stdafx.h"

#include "typelistCons.hpp"
#define CONSCELL

#include "typelist/insertionsort.hpp"

template<typename T, typename U>
struct SmallerThanT
{
	static constexpr bool value = sizeof(T) < sizeof(U);
};

#if 1	// where to place code in files so as to decrease coupling to specific implementations
void conslistest()
{
	using ConsList = Cons<int, Cons<char, Cons<short, Cons<double>>>>;
	using SortedTypes = InsertionSort<ConsList, SmallerThanT>;
	using Expected = Cons<char, Cons<short, Cons<int, Cons<double>>>>;
	std::cout << std::is_same_v<SortedTypes, Expected> << std::endl;
}
#endif


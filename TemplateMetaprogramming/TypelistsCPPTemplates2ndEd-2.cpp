#include <type_traits>
#include <iostream>
#include "typelist/insertsorted.hpp"

template<typename T, typename U>
struct SmallerThanT {
	static constexpr bool value = sizeof(T) < sizeof(U);
};

void testInsertionSort()
{
//	using Types = Typelist<int, char, short, double>;
	using Types = Typelist<char>;

	//using ST = InsertionSort<Types, SmallerThanT>;
//	std::cout << std::is_same<ST, Typelist<char, short, int, double>>::value
//		<< '\n';
}

#include "stdafx.h"

using namespace std;

template<int N>
struct Integral
{
	static constexpr int Value = N;
};


template<int...N>
struct List
{
	inline static std::tuple<Integral<N>...> values; // = make_tuple(N...);
	List() {}    //  : values{ make_tuple(N...) } {}
};


void useList()
{
	auto v = get<0>(List<10, 13>::values);
	auto x = v.Value;


	
}
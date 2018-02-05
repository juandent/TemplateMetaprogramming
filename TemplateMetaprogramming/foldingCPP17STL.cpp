#include "stdafx.h"

template <typename ... Ts>
auto sum(Ts ... ts)
{
	return (ts + ...);
}

template <typename R, typename ... Ts>
auto matches(const R& range, Ts ... ts)
{
	return (std::count(std::begin(range), std::end(range), ts) + ...);
}

void useSumFold()
{
	auto res = sum(3, 5, 7);
	std::string s1{ "Hello " };
	std::string s2{ "World" };
	auto concat = sum(s1,s2);

	std::vector<int> v{ 1,2,3,4,5 };
	auto r = matches(v, 2, 5);

}


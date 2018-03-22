#include "stdafx.h"

#include <set>


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


template<typename T, typename ...Ts>
bool insert_all(T& set, Ts ... ts)
{
	return (set.insert(ts).second && ...);
}

template<typename T, typename ...Ts>
bool within(T min, T max, Ts...ts)
{
	return ((ts >= min && ts <= max) && ...);
}

template<typename T, typename...Ts>
void insert_all(std::vector<T>& vec, Ts...ts)
{
	(vec.push_back(ts), ...);
}

void useSumFold()
{
	auto res = sum(3, 5, 7);
	std::string s1{ "Hello " };
	std::string s2{ "World" };
	auto concat = sum(s1,s2);

	std::vector<int> v{ 1,2,3,4,5 };
	auto r = matches(v, 2, 5);

	std::set<int> my_set{ 1,2,3 };
	auto all1 = insert_all(my_set, 4, 5, 6);
	auto all2 = insert_all(my_set, 7,8,2);

	auto in = within(3, 6, 4, 5, 6);
	auto in2 = within(3, 6, 4, 5, 7);

	insert_all(v, 10, 11, 12);
}


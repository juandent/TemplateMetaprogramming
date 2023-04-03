#include <algorithm>
#include <iostream>
#include <compare>
#include <vector>
#include <list>
#include <ranges>
#include <type_traits>
#include <concepts>
#include <optional>
#include <iterator>
#include <unordered_map>
#include <span>

namespace {
	void foo(auto beg, auto end)
	{
		auto v = std::ranges::subrange{ beg,end } | std::views::drop(4);

		if( v.begin() == v.end())
		{
			int i = 0;
		}
	}

	void printPairs(auto&& rg)
	{
		for( const auto& [key, val] : rg)
		{
			std::cout << key << ":" << val << " ";
		}
		std::cout << std::endl;
	}
}


void useSubrange()
{
	std::vector<int> coll{ 0,8,15,47,11,-1,13 };
	foo(coll.begin() + 2, coll.end());





	std::unordered_multimap<std::string, std::string> dict = {
		{ "strange" , "fremd"},
		{ "smart", "klug"},
		{ "car", "auto"},
		{ "smart", "raffiniert"},
		{ "trait", "Merkmal"},
		{ "smart", "elegant"}
	};
	auto [beg, end] = dict.equal_range("smart");

	printPairs(std::ranges::subrange{ beg, end } );

	std::list<int> lst{ 1,2,3,4,5,6,7,8 };


	std::vector<std::string> vec{ "New York", "Tokio", "Rio", "Berlin", "Sydney" };


	std::ranges::sort(std::span{ vec }.subspan(1, 3));

	for(auto& elem : std::span{vec}.last(3))
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	std::string s = "abc";
	std::string_view::iterator svi;
	{
		std::string_view sv = s;
		svi = sv.begin();
	}
	std::cout << *svi;
}


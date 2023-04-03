#include <iostream>
#include <compare>
#include <vector>
#include <list>
#include <ranges>
#include <type_traits>
#include <concepts>
#include <optional>
#include <iterator>


void useCounted()
{
	auto v = std::ranges::iota_view(1, 10);
	std::vector<int> vec{ 1,2,3,4,5,6,7,8,9 };
	auto p5 = std::ranges::find(vec, 5);
	auto v1 = std::views::counted(p5, 3);
	vec[5]++;
	auto v2 = std::views::counted(p5, 3);

	auto v3 = std::views::counted(vec.begin(), 3);



	std::list<int> lst{ 1,2,3,4,5 };
	auto l0 = std::views::common(lst);
	auto vt = std::views::take(lst, 3);
	
	
	auto l1 = std::views::common(vt);



	{
		std::list<std::string> coll{ "tic", "tac", "toe" };
		std::vector<std::string> v1;
		std::vector<std::string> v2;

		// for (std::move_iterator pos{ coll.begin() }; pos != std::move_sentinel{ coll.end() }; ++pos)
		// 	v2.push_back(*pos);

		std::vector<std::string> v4{ std::move_iterator{coll.begin()}, std::move_iterator {coll.end()} };

		// std::vector<std::string> v5{ std::move_iterator{coll.begin()}, std::move_sentinel{coll.end()} };

	}
}

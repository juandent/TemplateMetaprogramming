// constexpr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
#include <array>
#include <algorithm>
//#include <tuple>



struct Merchant { int id; };

consteval  bool has_merchant(const Merchant& selected)
{
	auto merchants = std::array{ Merchant{1}, Merchant{2}, Merchant{3}, Merchant{4}, Merchant{5} };
	return std::binary_search(merchants.begin(), merchants.end(), selected, [](auto a, auto b) {
		return a.id < b.id;
		});
}

int main()
{
	return has_merchant({ 4 });
}


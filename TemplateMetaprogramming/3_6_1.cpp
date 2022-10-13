#include <iostream>
#include <ranges>
#include <vector>
#include <string>



auto filterPrice(double max)
{
	return std::views::filter([max](auto e) { return e < max; });
}

auto addCurrency(const std::string& suffix)
{
	return std::views::transform([suffix](auto i) { return std::to_string(i) + suffix; });
}

void useFilter()
{
	const std::vector prices{ 3.95,6.0, 95.4, 10.95 };
	constexpr const char* suffix = " $";

	auto subView = prices | std::views::filter([](auto e) { return e < 10.0; }) | std::views::transform([suffix](auto i) { return std::to_string(i) + suffix; });

	for(auto v : subView)
	{
		std::cout << v << std::endl;
	}

	auto another = prices | filterPrice(10.0) | addCurrency(" $");

	for (auto v : another)
	{
		std::cout << v << std::endl;
	}

}

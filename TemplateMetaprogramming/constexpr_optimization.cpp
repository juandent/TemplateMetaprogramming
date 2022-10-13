#include <array>
#include <vector>
#include <algorithm>
#include <chrono>



namespace HasMerchant
{

	struct Merchant { int id; };

	consteval bool has_merchant(const Merchant& selected)
	{
		for (int s = 0; s < 10; ++s)
		{
			Merchant m{ 1 };
			auto merchants = std::array{ m, Merchant{1}, Merchant{2}, Merchant{3}, Merchant{4}, Merchant{5} };
			bool ok = std::binary_search(merchants.begin(), merchants.end(), selected, [](auto a, auto b) {
				return a.id < b.id;
				});
		}
		return true;
	}

	 consteval bool has_merchant2(const Merchant& selected)
	{
		auto merchants = std::vector{ Merchant{1}, Merchant{2}, Merchant{3}, Merchant{4}, Merchant{5} };
		return std::binary_search(merchants.begin(), merchants.end(), selected, [](auto a, auto b) {
			return a.id < b.id;
			});
	}


	void main()
	{
		{
			const auto first = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < 10'000'000; ++i)
			{}
			const auto second = std::chrono::high_resolution_clock::now();
			const auto elapsed = second - first;
			const auto el = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
			std::ignore = true;
		}
		const auto first = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10'000'000; ++i)
		{
			has_merchant({ 4 });
		}
		const auto second = std::chrono::high_resolution_clock::now();
		const auto elapsed = second - first;

		const auto el = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);


		std::ignore = true;
	}
}


#include <optional>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>
#include <numeric>
#include <chrono>
#include <gsl/gsl>
#include <unordered_map>
#include <iostream>
using namespace std::chrono;

// old style: custom for loops
std::optional<int> LastDayStableTemperatures()
{
	auto temperatures = std::vector<double>{ -3.,2.,0.,8.,-10. - 7. };

	for (std::size_t i =0; i < temperatures.size(); ++i)
		for (std::size_t j = i+1; j < temperatures.size(); ++j)
		{
			if (std::abs(temperatures[i] - temperatures[j]) > 5)
				return std::optional(i);
		}
	return std::nullopt;
}

std::optional<int> LastDayStableTemperaturesWithAlgo()
{
	auto temperatures = std::vector<double>{ -3.,2.,0.,8.,-10. - 7. };

	auto it = std::ranges::adjacent_find(temperatures, [](double first, double second)
		{
			return std::abs(first - second) > 5;
		});
	if(it != std::end(temperatures))
	{
		return std::optional(std::distance(std::begin(temperatures), it));
	}
	return std::nullopt;
}


std::string declarative_programming()
{
	using namespace std::ranges;
	using namespace std::literals;

	auto is_even = [](auto x) { return x % 2 == 0; };
	auto to_string = [](auto x) { return std::to_string(x); };

	auto my_range = views::iota(1) | views::filter(is_even) | views::take(2) | views::reverse | views::transform(to_string);

	auto res = std::accumulate(begin(my_range), end(my_range), ""s);
	return res;
}

using CustomerId = int;
CustomerId get_current_customer() { return 42; }

struct Merchant
{
	int id;
};

struct Item
{
	std::string name;
	std::optional<std::string> photo_url;
	std::string description;
	std::optional<float> price;
	time_point<system_clock> date_added;
	bool featured;
};
#if 0
std::ostream & operator<<(std::ostream os, const Item& item)
{
	auto stringify_optional = [](const auto& optional)
	{
		using optional_value_type = typename std::remove_cvref_t<decltype(optional)>::value_type;
		if constexpr (std::is_same_v<optional_value_type, std::string>)
		{
			return optional ? *optional : "missing";
		}
		else
		{
			return optional ? std::to_string(*optional) : "missing";
		}
	};
	auto item_added = system_clock::to_time_t(item.date_added);

	os << "name: " << item.name
		<< ", photo_url:  " << stringify_optional(item.photo_url)
		<< ", description: " << item.description
		<< ", price: " << std::setprecision(2) << stringify_optional(item.price)
		<< ", date_added: " << std::put_time(std::localtime(&item_added), "%c %Z")
		<< ", featured: " << item.featured << "\n";
	return os;

}
#endif
using namespace std::literals;

template<typename T, typename U = typename std::remove_cvref_t<T>::value_type, std::enable_if_t<std::is_same_v<U, std::string>, int> = 0>
std::string stringify_optional(const T& optional)
{
	return optional ? *optional : "missing"s;
}

template<typename T, typename U = typename std::remove_cvref_t<T>::value_type, std::enable_if_t<! std::is_same_v<U, std::string>, int> = 0>
std::string stringify_optional(const T& optional)
{
	return optional ? std::to_string(*optional): "missing"s;
}

std::ostream& operator<<(std::ostream os, const Item& item)
{
	auto item_added = system_clock::to_time_t(item.date_added);

	os << "name: " << item.name
		<< ", photo_url:  " << stringify_optional(item.photo_url)
		<< ", description: " << item.description
		<< ", price: " << std::setprecision(2) << stringify_optional(item.price)
		<< ", date_added: " << std::put_time(std::localtime(&item_added), "%c %Z")
		<< ", featured: " << item.featured << "\n";
	return os;

}

std::ostream& operator<<(std::ostream os, gsl::not_null< const Item*> item)
{
	os << item->name;
	return os;
}

enum class Category
{
	Food,
	Antiques,
	Books,
	Music,
	Photography,
	Handicraft,
	Artist
};

struct Store
{
	gsl::not_null<const Merchant*> owner;
	std::vector<Item> items;
	std::vector<Category> categories;
};


using Stores = std::vector<gsl::not_null<const Store*>>;
static const auto merchants = std::vector<Merchant>{ {17}, {29} };


Item it{ .name = "Honey", .photo_url = {}, .description = "Straight out of Compton's apiary", .price = 9.99f, .date_added = system_clock::now(), .featured = false };
Item it2{ .name = "ocypeck", .photo_url = {}, .description = "Tastee smoked cheese", .price = 1.23f, .date_added = system_clock::now() - 1h, .featured = true };
Category cat{ Category::Food };
Category cat2{ Category::Antiques };
Store s1{ &merchants[0],{it,it2}, {cat} };
Store s2{ &merchants[0],{it,it2}, {cat2} };

std::vector<Store> stores{
	s1,s2
};

//
// auto stores = std::vector<Store>{ Store {.owner = &merchants[0], .items = {
// 	Item{.name = "Honey", .photo_url = {}, .description = "Straight out of Compton's apiary", .price = 9.99f, .date_added = system_clock::now(), .featured = false},
// 	Item{.name = "ocypeck", .photo_url = {}, .description = "Tastee smoked cheese", .price = 1.23f, .date_added = system_clock::now() - 1h, .featured = true}},
// 	.categories = {
// 	Category{Category::Food}
// 	}
// } };


static auto get_favorite_stores_by_customer = std::unordered_map<CustomerId, Stores>{ {42, {&stores[0], &stores[1]}} };

Stores get_favorite_stores_for(const CustomerId & cust_id)
{
	return get_favorite_stores_by_customer[cust_id];
}

using Items = std::vector<gsl::not_null<const Item*>>;


Items get_featured_items_for_store(const Store& store)
{
	auto featured = Items{};
	const auto& items = store.items;
	for (auto& item : items)
	{
		if (item.featured)
		{
			featured.emplace_back(&item);
		}
	}
	return featured;
}

#if 1
Items get_all_featured_items(const Stores& stores)
{
	auto all_featured = Items{};
	for (const auto& store : stores)
	{
		const auto featured_in_stored = get_featured_items_for_store(*store);
		all_featured.reserve(all_featured.size() + featured_in_stored.size());
		std::copy(std::begin(featured_in_stored), std::end(featured_in_stored), std::back_inserter(all_featured));
	}
	return all_featured;
}
#endif


void order_items_by_date_added(Items& items)
{
	auto date_comparator = [](const auto& left, const auto& right) {
		return left->date_added > right->date_added;
	};
	std::sort(std::begin(items), std::end(items), date_comparator);
}

void render_item_gallery(const Items& items)
{
//	std::copy(std::begin(items), std::end(items), std::ostream_iterator<gsl::not_null<const Item*>>(std::cout, "\n"));
}

#if 0
namespace HasMerchant
{

	struct Merchant { int id; };

	constexpr bool has_merchant(const Merchant& selected)
	{
		auto merchants = std::array{ Merchant{1}, Merchant{2}, Merchant{3}, Merchant{4}, Merchant{5} };
		return std::binary_search(merchants.begin(), merchants.end(), selected, [](auto a, auto b) {
			return a.id < b.id;
			});
	}

	void main()
	{
		bool has = has_merchant({ 4 });
		std::ignore = has;
	}
}
#endif

void showCasingFeaturedGallery()
{
	Stores stores = get_favorite_stores_for(42);

	auto selected_items = get_all_featured_items(stores);

	order_items_by_date_added(selected_items);
	render_item_gallery(selected_items);
}



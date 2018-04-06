#include "stdafx.h"

#include <utility>
#include <set>

void autoDeductionOfTemplate()		// NOT YET in VS 2017
{
	//	std::pair my_pair{ 123, "abc" };
	std::pair<int, char*> other_pair{ 123, "abc" };
}


template<typename T>
struct sum
{
	T value;

	template<typename ...Ts>
	sum(Ts&& ... values) : value{ (values + ...) } {}

};

// not yet in VS 2017
//template<typename...Ts>
//sum(Ts&&...ts)->sum<std::common_type_t<Ts...>>;


template<typename T>
class addable
{
	T val;
public:
	addable(T v) : val{ v } {}

	template<typename U>
	T add(U x) const
	{
		if constexpr(std::is_same_v<T, std::vector<U>>)
		{
			auto copy{ val };
			for (auto& n : copy)
			{
				n += x;
			}
			return copy;
		}
		else
		{
			return val + x;
		}
	}
};

	void useAddable()
	{
		std::vector<int> v{ 1,2,3,4 };
		int p = 'a';
		auto ad = addable<int>(p);
		auto xx = ad.add('b');

		auto res = addable<std::vector<int>>{v}.add(10);
	}

	using namespace std;

	template<typename C, typename T>
	void insert_sorted(C& v, const T& item)
	{
		const auto iterator_pos{ lower_bound(begin(v), end(v), item) };
		v.insert(iterator_pos, item);
	}

		
	//mbozzi - cplusplus.com

	template <template <typename...> class, typename>
	struct is_instance_of : std::false_type {};

	template <template <typename...> class Tm, typename... Ts>
	struct is_instance_of<Tm, Tm<Ts...>> : std::true_type {};

	template <typename T>
	constexpr bool is_instance_of_set = is_instance_of<std::set, T>::value;

	static_assert(is_instance_of_set<std::set<int>>);
	static_assert(!is_instance_of_set<std::vector<int>>);


	void useSortedInserting()
	{
		using Container = set<string>;
		Container v{ "Juan", "Leslie", "Kisha" };

		if constexpr(!is_same_v < Container, set<string>> && !is_same_v<Container, list<string>>)
		{
			assert(!is_sorted(v.begin(), v.end()));
			sort(v.begin(), v.end());
			assert(is_sorted(v.begin(), v.end()));
		}

		insert_sorted(v, "Ana");
		insert_sorted(v, "Julia");

		for (auto& it : v)
		{
			cout << it << ", ";
		}
		cout << endl;
	}


	void insertionWithHints()
	{
		std::unordered_map<string, size_t> m{ {"b",1}, {"c",2}, {"d",3} };

		auto insert_iter{ std::end(m) };

		for (const auto& s : { "z", "y", "x", "w" })
		{
			insert_iter = m.insert(insert_iter, { s,1 });
		}

		m.insert(std::end(m), { "a", 1 });

		for (const auto&[key, value] : m)
		{
			cout << "\"" << key << "\"" << "\":" << value << ", ";
		}
		cout << endl;
	}

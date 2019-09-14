#include <string>
#include <cstddef>
#include <iostream>
#include <ostream>
#include  <vector>
//#include <experimental/    <concepts>
using namespace std::literals;

// Declaration of the concept "Hashable", which is satisfied by
// any type T such that for values a of type T,
// the expression std::hash<T>{}(a) compiles and its result is convertible to std::size_t
#if 0
template<typename T>
concept Hashable = requires(T a) {
	{ std::hash<T>{}(a) }->std::convertible_to<std::size_t>;
};

#endif

using namespace std;

template <typename C>
auto opt_print(const C& container, ostream& os )
{
	return[end_it = end(container),&os](const auto& item) {
		if (item != end_it) {
			os << *item << "\n";
		}
		else {
			os << "<end>\n";
		}
		return "end";
	};
}

struct city {
	string name;
	unsigned population;
};

ostream& operator<<(ostream& os, const city& city) {
	return os << "{" << city.name << ", " << city.population << "}";
}



void use_opt_print()
{
	vector<int> v{ 1,6,9 };

	auto printer = opt_print(v, cout);

////	vector<int> vv{ 2,99 };

	auto ret = printer(v.begin());
	//printer(v.end());

	int i = 0;

	vector<city> vc{ {"San Jose", 2'000'000},
		{"Limon", 150'000} };

	auto vc_printer = opt_print(vc, cout);

	vc_printer(vc.begin());
}

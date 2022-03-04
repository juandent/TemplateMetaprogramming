

// #include "stdafx.h"


#include <string>
#include <variant>
#include <iostream>
#include <utility>
#include <vector>


class DerivedVar : public std::variant<int, std::string>
{};

void useVariant()
{
	using namespace std;

	using VAR = std::variant<int, long long>;
	auto obj = std::variant_size<VAR>{};
	std::variant_size<VAR>::value_type vt = obj;
	constexpr  int v = std::variant_size<VAR>::value;
	using TYPE = std::variant_alternative_t<1, VAR>;



	DerivedVar d = { {"Hello"} };
	cout << d.index() << endl;

	auto ok = holds_alternative<int>(d);


	auto x = std::get<1>(d);
      // if( x == std::variant_npos) {
        
      // }
	cout << x << endl;

	using TT = std::variant<int, string>;
	TT tt{ 50 };

	auto var = std::in_place_type<int>;

	using IntOrDouble = std::variant<int, double>;

	vector<IntOrDouble> coll{ 42, 7.7, 0, -0.7 };

	double sum{};
	for (const auto& elem : coll) {
		sum += std::visit([](const auto& val)->double
			{
				return val;
			}, elem);
	}
  }


template<typename...Ts>
struct overload : Ts...
{
	using Ts::operator()...;
};

// base types are deduced from passed arguments
template<typename...Ts>
overload(Ts...)->overload<Ts...>;


struct S
{
	operator int() { throw "exception"; }
};


void useOverloadMixins()
{
	std::variant<int, std::string> var{ 42 };

	std::visit(overload{
		[](int  i) { std::cout << i << std::endl; },
		[](const std::string& s)  { std::cout << s << std::endl; }
			}, var);

	auto twice = overload{
		[](int& i) { i *= 2; },
	  [](std::string& s) { s += s; }
	};

	std::visit(twice, var);

	var = "hi";
	std::visit(twice, var);

	std::variant<int, std::string> vempty{};

	try
	{
		vempty = S{};
	}
	catch (...)
	{
		if( vempty.valueless_by_exception())
		{
			int i = 0;
		}
		auto e = ~0;
		if( e == std::variant_npos)
		{
			int i = 0;
		}
		
		if (vempty.index() == std::variant_npos) {
			// no value set
			int i = 0;

		}
	}
}
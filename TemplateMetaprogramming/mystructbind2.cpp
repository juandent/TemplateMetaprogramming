#include "stdafx.h"
#include <utility>  // for tuple-like API

// using namespace std;

struct Customer
{
private:
	std::string first;
	std::string last;
	long val;
public:
	Customer(std::string f, std::string l, long v)
		: first{ std::move(f) }, last{ std::move(l) }, val{ v } {}

	const std::string& firstname() const
	{
		return first;
	}
	std::string& firstname()
	{
		return first;
	}
	const std::string& lastname() const
	{
		return last;
	}
	std::string& lastname()
	{
		return last;
	}
	long value() const
	{
		return val;
	}
	long& value()
	{
		return val;
	}
};


// template<typename T>
// struct tuple_size
// {
// };

template<>
struct std::tuple_size<Customer>
{
	static constexpr size_t value = 3;
};


template<size_t Idx>
struct std::tuple_element<Idx, Customer>
{
	using type = std::string;
};

template<>
struct std::tuple_element<2, Customer>
{
	using type = long;
};


template<size_t Idx>
decltype(auto) get(Customer& c)
{
	static_assert(Idx < 3);

	if constexpr (Idx == 0)
	{
		return c.firstname();
	}
	else if constexpr (Idx == 1)
	{
		return c.lastname();
	}
	else
	{
		return c.value();
	}
}

template<size_t Idx>
decltype(auto) get(const Customer& c)
{
	static_assert(Idx < 3);

	if constexpr (Idx == 0)
	{
		return c.firstname();
	}
	else if constexpr (Idx == 1)
	{
		return c.lastname();
	}
	else
	{
		return c.value();
	}
}

template<size_t Idx> decltype(auto) get(Customer&& c)
{
	static_assert(Idx < 3);

	if constexpr (Idx == 0)
	{
		return std::move(c.firstname());
	}
	else if constexpr (Idx == 1)
	{
		return std::move(c.lastname());
	}
	else
	{
		return c.value();
	}
}

void useDeclTypeAuto()
{
	Customer c{ "Tim", "Starr", 42 };
	auto [f, l, v] = c;
	std::cout << "f/l/v:    " << f << ' ' << l << ' ' << v << '\n';

	// modify structured bindings via references:
	auto&& [f2, l2, v2] = c;
	std::string s{ std::move(f2) };
	f2 = "Ringo";
	v2 += 10;
	std::cout << "f2/l2/v2: " << f2 << ' ' << l2 << ' ' << v2 << '\n';
	std::cout << "c:        " << c.firstname() << ' '
		<< c.lastname() << ' ' << c.value() << '\n';
	std::cout << "s:        " << s << '\n';
}

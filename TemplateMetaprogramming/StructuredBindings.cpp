#include "stdafx.h"

struct MyStruct
{
// private:
	int i = 0;
	std::string s;
};


MyStruct getStruct()
{
	return MyStruct{ 42, "hello" };
}

template<typename T>
struct Temp
{
	using Type = T;
	static Type* p;
};


auto getArr() -> int(&)[2];

std::array<int,4> getArray()
{
	std::array<int, 4> ar = { 1,2,3,4 };
	return ar;
}

void useMyStruct()
{

	const auto& [a, b, c, d] = getArray();

	// auto& [a, b, c, d] = getArray();    // ERROR (prvalue to non const reference is not allowed)
	
	auto& [o, l] = getArr();

	o += 10;
	
	MyStruct ms;
	auto [n, m] = ms;

	auto [id, val] = getStruct();


	const auto& [k, p] = ms;

	//auto w = Temp< decltype(k)>;

	//k = 14;
	auto kk = ms.i;

	
	MyStruct mmm{ 42, "Jim" };

	auto&& [ss, nn] = mmm;

	ss = 10;
	nn = "John";

	std::string sss = std::move(nn);

	std::cout << "nn = " << nn << std::endl;

	std::cout << "mmm.s = " << mmm.s << std::endl;

}


auto getArr() -> int(&)[2]
{
	int arr[2] = {3,9};
	return arr;
}


#include <functional>

void useSearcher()
{
	std::string in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
		" sed do eiusmod tempor incididunt ut labore pisci et dolore magna aliqua";

	std::string needle = "pisci";

	std::boyer_moore_searcher bmsearcher{ needle.begin(), needle.end() };

	for( auto [beg,end] = bmsearcher(in.begin(), in.end());
		beg != in.end();
		std::tie( beg, end) = bmsearcher(end, in.end()))
	{
		std::cout << "found '" << needle << "' at offset " << beg - in.begin() << "-" << end - in.begin()
			<< std::endl;

		auto start_offset = beg - in.begin();

		auto substr = in.substr(start_offset);
		std::cout << substr << std::endl;
	}	
}

#if 0
namespace juan
{
	struct Customer
	{
		std::string name;
		std::string last;
		int age;
	};


	template<typename T>
	struct tuple_size
	{
	};

	template<>
	struct tuple_size<Customer>
	{
		static constexpr size_t value = 3;
	};

	template<size_t Idx, typename Type >
	struct tuple_element
	{
	};

	template<>
	struct tuple_element<0, Customer>
	{
		using type = std::string;
	};

	template<>
	struct tuple_element<1, Customer>
	{
		using type = std::string;
	};

	template<>
	struct tuple_element<2, Customer>
	{
		using type = long;
	};


	template<size_t idx, typename U>
	constexpr const auto& getauto(const U& u)
	{
	}

	template<>
	constexpr  const auto& getauto<0>(const Customer& c)
	{
		return c.name;
	}


	template<size_t idx, typename U>
	const typename tuple_element<idx, U>::type& get( const U& u)
	{
	}

	template<>
	const typename tuple_element<0, Customer>::type&  get<0>( const Customer& c)
	{
		return c.name;
	}

	template<>
	const typename tuple_element<1, Customer>::type& get<1>(const Customer& c)
	{
		return c.last;
	}

	template<>
	const typename tuple_element<2, Customer>::type& get<2>(const Customer& c)
	{
		return c.age;
	}

}
#endif

template<typename T>
struct Reveal
{
	using Type = T;
	Reveal() = delete;
};


// namespace dent
// {
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

//}

	// template<typename T>
	// struct ::std::tuple_size
	// {
	// };


template<>
struct std::tuple_size<Customer>
{
	static constexpr size_t value = 3;
};

template<size_t Idx, typename Type >
struct std::tuple_element
{
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

template<size_t Idx>
decltype(auto) get(Customer&& c)
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



void useDeclType()
{
//	using namespace dent;
	
	Customer cust{ "Tim", "Starr", 42 };

	auto [f, l, v] = cust;

	//f = "john";
}

#if 0
void useAPI()
{
	{
		using namespace juan;

		Customer c{ "juan", "dent", 59 };
		auto name = get<0>(c);
		auto last = get<1>(c);
		auto age = get<2>(c);
		auto next = getauto<0>(c);

		tuple_element<2, Customer>::type* p;
		constexpr size_t s = tuple_size<Customer>::value;
	}
	{
		using namespace dent;

		
	}
	//Reveal<decltype(p)>();
	
}

#endif

#include "stdafx.h"

struct MyStruct
{

	int i = 0;
	std::string s{};
public:
	MyStruct() = default;
	MyStruct(int i, std::string s) : i{i}, s{s} {}
	int getI() const { return i; }
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

std::vector<int> getIntVector()
{
	std::vector<int > vec{ 1,2,5,88 };
	return vec;
}

void useMyStruct()
{

	// auto [tt, jj, kkk, ll] = getIntVector();

	
	const auto& [a, b, c, d] = getArray();

	auto arreglo = getArray();
	

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

	MyStruct tttt{ 31, "Juan" };

	auto [ssss, nnn] = tttt;

	auto nnnn = std::move(nnn);

	int i = ssss;
}


auto getArr() -> int(&)[2]
{
	int arr[2] = {3,9};
	return arr;
}

auto getArrByValue()
{
	int arr[2]{ 3,9 };
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


struct Customer
{
	void set_name(const std::string& name)
	{
		this->name = name;
	}

	void set_last(const std::string& last)
	{
		this->last = last;
	}

	void set_age(int age)
	{
		this->age = age;
	}

	[[nodiscard]] const std::string& get_name() const
	{
		return name;
	}


	[[nodiscard]] const std::string& get_last() const
	{
		return last;
	}


	[[nodiscard]] int get_age() const
	{
		return age;
	}

	[[nodiscard]] std::string& get_name()
	{
		return name;
	}

	[[nodiscard]] std::string& get_last()
	{
		return last;
	}

	[[nodiscard]] int& get_age()
	{
		return age;
	}

	Customer(std::string name, std::string last, int age)
		: name(std::move(name)),
		last(std::move(last)),
		age(age)
	{
	}
private:
	std::string name;
	std::string last;
	int age;
};

template<typename T>
struct ::std::tuple_size
{

};

template<>
struct ::std::tuple_size<Customer>
{
	static constexpr int value = 3;
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
	using type = int;
};


#ifdef NO_CONSTEXPR_IF

template<> decltype(auto) get<0>(Customer& c)  { return c.get_name(); }
template<> decltype(auto) get<1>(Customer& c) { return c.get_last(); }
template<> decltype(auto) get<2>(Customer& c) { return c.get_age(); }

template<> decltype(auto) get<0>(const Customer& c) { return c.get_name(); }
template<> decltype(auto) get<1>(const Customer& c) { return c.get_last(); }
template<> decltype(auto) get<2>(const Customer& c) { return c.get_age(); }

template<> decltype(auto) get<0>(Customer&& c) { return c.get_name(); }
template<> decltype(auto) get<1>(Customer&& c) { return c.get_last(); }
template<> decltype(auto) get<2>(Customer&& c) { return c.get_age(); }


#else



template<std::size_t I> decltype(auto) get(Customer& c)
{
	static_assert(I < 3);

	if constexpr (I == 0)
	{
		return c.get_name();
	}
	else if constexpr (I == 1)
	{
		return c.get_last();
	}
	else
		return c.get_age();
}

template<std::size_t I> decltype(auto) get(const Customer& c)
{
	static_assert(I < 3);

	if constexpr (I == 0)
	{
		return c.get_name();
	}
	else if constexpr (I == 1)
	{
		return c.get_last();
	}
	else
		return c.get_age();
}


template<std::size_t I> decltype(auto) get(Customer&& c)
{
	static_assert(I < 3);

	if constexpr (I == 0)
	{
		return std::move(c.get_name());
	}
	else if constexpr (I == 1)
	{
		return std::move(c.get_last());
	}
	else
		return c.get_age();
}

#endif

Customer getCustomer()
{
	return Customer{ "Juan","Dent", 60 };
}

void useCustomer()
{
	Customer c{ "Tim", "Stark", 42 };
	auto [f, l, a] = c;
	++a;

	auto [ff, ll, aa] = getCustomer();
	++aa;

	const Customer d{ "Leslie","Hulse", 52 };
	auto [fff,lll,aaa] = d;

	auto&& x = getCustomer();

	int i = 0;
}



template<typename T>
struct Reveal
{
	using Type = T;
	Reveal() = delete;
};




namespace dent
{
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

}

	// template<typename T>
	// struct ::std::tuple_size
	// {
	// };

#if 0
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
#endif



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


template<typename T>
void func_for_x(T param)
{
	int i = 0;
}

template<typename T>
void func_for_cx(const T param)
{
	int i = 0;
}

template<typename T>
void func_for_rx(const T& param)
{
	int i = 0;
}


void useTypeDeduction()
{
	auto x = 27;
	
	func_for_x(27);

	func_for_cx(x);
	
	func_for_rx(x);
	
	auto& r = x;

	const auto cx = x;
	const auto& rx = x;

	
}


namespace overload
{
	// void f(int&& x)
	// {
	//
	// }

	void f(int& i)
	{

	}

	void f(int i)
	{
		
	}

	int&& gg()
	{
		static int i{ 9 };
		return std::move(i);
	}

	void callReferenceOverload()
	{
		f(gg());

		f(28);

		int x = 34;

		// f(x);

	}
}
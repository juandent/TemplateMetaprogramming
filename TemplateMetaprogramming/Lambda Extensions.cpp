#include "stdafx.h"

#include <thread>


constexpr auto squared = [](auto val)
{
	return  val * val;
};

std::array<int, squared(5)> a;

auto squared2 = [](auto val) constexpr
{
	static int a = 1;
	
	return  val * val;
};

//std::array<int, squared2(5)> b;



constexpr auto squared3 = [](auto val) constexpr
{
	static int a = 1;

	return  val * val;
};

void usesquared3()
{
	auto i = 44;
	auto j = squared3(44);
	
}



constexpr auto squared4 = [](auto val) constexpr
{
	return  val * val;
};

constexpr decltype(auto) squared5 = [](auto val) constexpr
{
	return  val * val;
};


void useConstexprLambda()
{
	int n = 5;
	constexpr auto r = squared4(5);
	auto rs = squared4(n);
	auto&& s = squared5(5);
	auto a = squared5(9);
	int ret = 5;
	ret = squared5(5);

}


constexpr auto hashed = [](const char* str) constexpr
{
	std::size_t hash = 5381;
	while(*str != '\0')
	{
		hash = hash * 33 ^ *str++;
	}
	return hash;
};


std::array arr{ hashed("beer"),
	hashed("wine"),
	hashed("water") };



auto hashed_extended = [](const char* str, auto combine)
{
	std::size_t hash = 5381;
	while (*str != '\0')
	{
		hash = combine(hash, *str++);
	}
	return hash;
};


constexpr std::size_t hv1{ hashed_extended("beer", [](auto hash, char c)
{
	return hash * 33 + c;
}
) };


using namespace std;

class Data
{
	string name;
public:
	Data( const string& n) : name{n} {}

	auto startThreadWithCopyOfThis() const
	{
		using namespace std::literals;
		thread t{ [a=*this]
		{
			this_thread::sleep_for(3s);
			cout << a.name << endl;
		} };

		return t;
	}
};


void useData()
{
	thread t;
	{
		Data d{ "hello" };
		t = d.startThreadWithCopyOfThis();
	}  // d is no longer valid
	t.join();
}

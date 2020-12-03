#include "stdafx.h"

using namespace std;

class Base
{
public:
	void a() {}
	void b() {}
	void c() {}
};

class Derived : private Base
{
public:
	using Base::a, Base::b, Base::c;
};

template<typename ...Ts>
struct overload : Ts...
{
	using Ts::operator()...;
};


template<typename ...Ts>
overload(Ts...)->overload<Ts...>;

auto twice = overload{
	[](string& str)
{
	str += str;
},
[](auto& v)
{
	v *= 2;
} };


void useOverload()
{
	int i = 42;
	twice(i);
	cout << i << endl;
	string s = "hi";
	twice(s);
	cout << s << endl;
}


template<typename T>
class Base2
{
	T value{};
public:
	Base2() {}
	Base2(T v) : value{v} {}
};

template<typename ...Types>
class Multi : private Base2<Types>...
{
public:
	using Base2<Types>::Base2...;
	using Base2<Types>::operator=...;
};


void useMulti()
{
	using MultiISB = Multi<int, string, bool>;

	MultiISB m1{ 42 };
	MultiISB m2{ "hello"s };
	MultiISB m3{ true };

	
}












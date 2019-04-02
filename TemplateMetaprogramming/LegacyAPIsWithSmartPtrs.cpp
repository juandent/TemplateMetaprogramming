#include "stdafx.h"
#include <string>

using namespace std;

class Foo
{
	string name;
	Foo(string n) : name{ n } { cout << "CTOR " << name << endl; }
	~Foo() { cout << "DTOR " << name << endl; }
public:
	static Foo* create_foo(string s)
	{
		auto ret = new Foo{ move(s) };
		return ret;
	}
	static void destroy_foo(Foo* p)
	{
		delete p;
	}
};

shared_ptr<Foo> make_shared_foo(string s)
{
	auto ret =  shared_ptr<Foo>{ Foo::create_foo(move(s)), Foo::destroy_foo };
	return ret;
}

unique_ptr<Foo, void (*)(Foo*)> make_unique_foo(string s)
{
	return { Foo::create_foo(s), Foo::destroy_foo };
}

void  useLegacyAPIs()
{
	using namespace std::literals::string_literals;

	string lvalue{ "lvalue" };

	auto psl{ make_shared_foo(lvalue) };

	auto ps{ make_shared_foo("shared"s) };
	auto pu{ make_unique_foo("unique"s) };
}

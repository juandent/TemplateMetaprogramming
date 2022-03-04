


#include <any>
#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std::string_literals;


void useAny()
{
	using namespace std;

	std::any a = "Hello";
	std::any b = 4.3;
	a = "Juan"s;
	std::any_cast<std::string&>(a) = "world";
	auto s = std::any_cast<std::string>(a);


	auto p = std::any_cast<std::string>(&a);
	if( p!= nullptr)
	{
		auto x = *p;
	}

	vector<any> v;
	v.push_back(42);
	v.push_back("Hello"s);
	any a4{ in_place_type<long>, 590 };
	any a5{ in_place_type<string>, "hello" };
	v.push_back(a4);
	v.push_back(a5);
	any a6{ in_place_type<const char*>, "hello world" };
	v.push_back(a6);

	for(const auto& a : v)
	{
		if( auto pa = any_cast<const string>(&a); pa != nullptr)
		{
			cout << "string " << *pa << endl;
		}
		else if( auto pa = any_cast<const int>(&a); pa != nullptr)
		{
			cout << "int " << *pa << endl;
		}
	}

	auto sc = [](int x, int y)
	{
		return abs(x) < abs(y);
	};

	any a8{ in_place_type<set<int, decltype(sc)>>, {4,8,-7,-2,0,5}, sc };

	auto y = any_cast<set<int, decltype(sc)>>(a8);

	auto z = any_cast<set<int, decltype(sc)>&>(a8);

	string st{ "Hello Dear" };
	any a9;
	a9 = move(st);
	any a10{ "juan"s };

	st = move(any_cast<string&>(a10));
	st = move(any_cast<string&>(a10));
	a10 = "leslie"s;
	// moves a copy of a10 contents:
	st = move(any_cast<string>(a10));

}

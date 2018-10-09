#include "stdafx.h"
#include <string>

using namespace std;

template<int& Counter>
struct LocalIncrementer
{
	LocalIncrementer() { Counter = Counter + 1; }
	~LocalIncrementer() { Counter = Counter - 1; }
};

int x = 5;
//static int& y = x;

void useLocalIncrementer()
{
	LocalIncrementer<x> inc{};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of non-type parameters.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////

class Base
{
	int m_x;
public:
	constexpr Base(int x) : m_x{ x } {}
};

class Converter
{
	Base m_base;
public:
	constexpr Converter(int x) : m_base{ x } {}
	constexpr operator Base*() { return &m_base; }
};

class Derived : public Base
{
public:
	using Base::Base;
};

void useDerived()
{
	Base* p = new Derived{ 5 };
	delete p;
}

template <typename T, T val>
struct UseVal
{

};

Base    base{ 9 };
Derived der{ 8 };
Converter conv{ 5 };

void theseWillWorkInCPP17()
{
	UseVal<Base*, &base> obj;
	//UseVal<Base*, &der> obj2;
	Base* p = &der;
	Base* pp = conv;

	//UseVal<Base*, conv> obj3;
}

struct X
{
	static bool b;
	const int n = 55;
	constexpr operator int() const { return 42; }
};

constexpr X anX{ 50 };

void useX()
{
	UseVal< const X*, &anX > * c7;

}


template <typename ...Mixins>
class Point : public Mixins...
{
	double x, y, z;
public:
	Point(Mixins...mixins) : Mixins(mixins)...{}

	template<typename Visitor>
	size_t visitMixins(Visitor visitor)
	{
		return visitor(static_cast<Mixins&>(*this)...);
	}
};

struct Color {
	char red, green, blue;

	void print()
	{
		cout << static_cast<int>(red) <<
			static_cast<int>(green) <<
			static_cast<int>(blue) << endl;
	}
	int value()
	{
		return red + green + blue;
	}
};

struct Label
{
	std::string name;
	void print()
	{
		cout << name << endl;
	}
};

///Point<Color, Label> p;	// inherits from both Color and Label

template<typename ...Types>
void print(Types ... values)
{

}

template<typename Head>
void print(Head val)
{
	cout << val << endl;
}

template<typename Head, typename ...Tail, typename = enable_if_t<(sizeof...(Tail) > 0)>>
void print(Head val, Tail... vs)
{
	print(val);
	print(vs...);
}

namespace Non_Type_Parameters
{
	struct ColorLabelVisitor
	{
		size_t operator()(Color& c, Label& l)
		{
			c.print();
			l.print();
			return c.value();
		}
	};

	void usePrint()
	{
		print("C++", 2011, 5.777);

		ColorLabelVisitor visitor;

		Point<Color, Label> pcl{ {0x7F, 0, 0x7F}, {"center"} };
		auto ret = pcl.visitMixins(visitor);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of non-type parameters.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////

// Fold expressions
namespace FoldExpressions
{
	// without fold expressions:
	constexpr bool and_all() { return true; }

	template<typename T>
	constexpr bool and_all(T cond) { return cond; }

	template<typename T, typename ...Ts>
	constexpr bool and_all(T cond, Ts...conds)
	{
		return cond && and_all(conds...);
	}


	void useAndAll()
	{
		constexpr bool res = and_all(1, 44, "s", 0);

	}
#if 0	// compiler not there yet!

	// using fold expressions (C++17)
	template<typename...T>
	auto foldAnd(T...s)->bool
	{
		//return (... && s);	// ((s1 && s2) && s3).........
		return (s && ...);	// (1 && ( 44 && ( "s" && (0 && true))))
	}

	void useFold()
	{
		bool res = foldAnd(1, 44, "s");
	}
#endif
}
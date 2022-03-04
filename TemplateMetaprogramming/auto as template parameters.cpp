#include "stdafx.h"

using namespace std;


template<auto N> class S
{};


S<42> s1;		// type of N is int
S<'f'> s2;		// type of N is char

//S<2.5> s3;		// ERROR cannot be double!


template<typename T, auto N>
class A
{
public:
	A(const std::array < T, N>&) {}
	A( T(&)[N] ) {}
};

A a1{ "hello" };	// T is const char, N is 6 being size_t

array<double, 10> arr;

A a2{ arr };

template<auto...VS> struct HeteroValueList
{};

template< auto v1, decltype(v1)...VS>
struct HomoValueList  {};

HeteroValueList < 1, 2, 'a'> hl;

//HomoValueList<11, 22, true, "hello" > hl2;

HomoValueList<11, 22, true > hl3;


template<auto Sep = ' ', typename First, typename...Args>
void print( const First& f, const Args& ... args)
{
	cout << f;
	auto outWithSep = [Sep](const auto& arg)
	{
		cout << Sep << arg;
	};
	(..., outWithSep(args));
	cout << endl;
}

void usePrint()
{
	
}



template<typename T, T v>
struct constant
{
	static constexpr T value = v;
};

using i = constant<int, 42>;
using c = constant<char, 'a'>;


template<auto t>
struct constant2
{
	static constexpr auto value = t;
};

using j = constant2<42>;
using d = constant2<'a'>;


namespace UsingDecltypeAuto
{

	template<decltype(auto) N>
	struct S
	{
		void printN() const
		{
			cout << "N: " << N << endl;
			cout << typeid(N).name() << endl;
		}
	};

	struct C
	{
		int val;
	};

	decltype(auto) retTemp()
	{
		return C{ 4 };
	}

	decltype(auto)
	// auto
	ret()
	{
		int a = 32;
		auto c = retTemp();
		return move(c);
	}

	static const int c = 42;
	static int v = 42;
	
	void useDeclType()
	{
		decltype(auto) a = ret();
		decltype(auto) aa = retTemp();
		S<c> ac;
		S<(c)> acc;

	}


}


namespace JD
{
	struct Widget
	{
		[[nodiscard]] explicit Widget(const std::string& s)
			: s(s)
		{
		}

		Widget(Widget& rhs)
			: s(std::forward<std::string>(rhs.s))
		{}

	private:
		std::string s;
	};

	[[nodiscard]] std::string GetString()
	{
		return "Leslie"s;
	}
	
	void useWidget()
	{
		std::string ss = "juan";
		Widget w{ ss };
		Widget q{ w };
		GetString();
		Widget b{ GetString() };
	}
	
}


namespace Packs_cppreference
{


	template<typename ...Ts, int... N>
	void g(Ts(&...arr)[N])
	{
		int native[] = { N... };
	
	}


	void useG()
	{
		int n[1];

		g("abc", n); // Ts (&...arr)[N] expands to 

		// const char (&)[4], int(&)[1]

	}
	

}
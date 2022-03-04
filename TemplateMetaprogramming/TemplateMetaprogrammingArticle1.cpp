#include "stdafx.h"


template<int N> requires (N > 0)
struct Factorial
{
	static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<1>
{
	static constexpr int value = 1;
};

int factorial(int num)
{
	return (num < 2) ? 1 : num * factorial(num - 1);
}

template<int N> requires (N > 0)
constexpr int FactorialFunc()
{
	return N * FactorialFunc<N - 1>();
}

template<>
constexpr int FactorialFunc<1>()
{
	return 1;
}

constexpr int factorialAlt(int num)
{
	return (num < 2) ? 1 : num * factorialAlt(num - 1);
}


constexpr int res = factorialAlt(3);

void useFactorial()
{
	using fact3 = Factorial<3>;
	typedef Factorial<3> Fact3;
	std::cout << fact3::value << Fact3::value  << std::endl;

	static constinit const int IntVal = 3;
	using FactIntVal = Factorial<IntVal>;

	int var = 3;
	auto val = factorial(var);

	constexpr int ret = FactorialFunc<3>();

	int variable = 3;
	constexpr int res = factorialAlt(3);
	int runtime_res = factorialAlt(variable);

}

// Ch 28 [S,2013]

template<unsigned N, typename ...Cases>
struct select;

template<unsigned N, typename Head, typename...Tail>
struct select<N, Head, Tail...> : select<N-1, Tail...>
{};

template<typename Head, typename...Tail>
struct select<0, Head, Tail...>
{
	using type = Head;
};

void useSelect()
{
	using type = select<3, char, short, int, long, long long>::type;
	static_assert(std::is_same<type, long>::value);
}


template<int N>
class StringLiteral
{
public:
	constexpr StringLiteral(char const (&str)[N])
	{
		std::copy(str, str + N, data);
	}
	char data[N];
};


template<StringLiteral str>
class ClassTemplate {};

void useLiteral()
{
	ClassTemplate<"juan"> ctj;

}
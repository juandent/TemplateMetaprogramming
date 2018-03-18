////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	Meta_ErwinUnruh.cpp
//
// summary:	Implements the first metaprogram created in C++ by erwin unruh 
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	The is prime. </summary>
///
/// <remarks>	p > i is assumed	
/// 			Juan Dent, 16/3/2018. </remarks>
///
/// <typeparam name="p">	Type of the p. </typeparam>
/// <typeparam name="i">	Generic type parameter. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<int p, int i>
struct is_prime
{
	enum { pri = (p == 2) || ((p%i) && is_prime< ((i > 2) ? p : 0), i - 1 >::pri) };
};

template<>
struct is_prime<0, 0>
{
	enum { pri = 1 };
};

template<>
struct is_prime<0, 1>
{
	enum { pri = 1 };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Used to generate error when D is attempted to be 
/// 				initialized with a non-pointer or an integer that is not zero
/// 				(only integer convertible to void* is 0) </summary>
///
/// <remarks>	Juan Dent, 16/3/2018. </remarks>
///
/// <typeparam name="i">	Generic type parameter. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<int i>
struct D
{
	D(void*) {};
};

template<int i>
struct CondNull
{
	static int const value = 1;
};

template<>
struct CondNull<0>
{
	static void* value;
};

void* CondNull<0>::value = 0;

#if 0
template<int i>
constexpr const char* iToCompileTimeStr()
{
	static char buffer[30];
	itoa(i, buffer, 10);
	return buffer;
}
#endif




template<int i, char* buffer, int N>
struct SetDigit
{
	constexpr static void doIt()
	{
		int digit = i % 10;
		buffer[N] = digit + '0';
		SetDigit<i / 10, buffer, N-1>::doIt();
	}
};

template<char* buffer, int N>
struct SetDigit<0,buffer, N>
{
	constexpr static void doIt()
	{
		buffer[N]= ' ';
		SetDigit<0, buffer, N-1>::doIt();
	}
};

template<char* buffer>
struct SetDigit<0, buffer, 0>
{
	constexpr static void doIt()
	{
		buffer[0] = ' ';
	}
};


struct IntToStr
{
	constexpr static std::size_t MAX = 10;
	static inline char buffer[MAX];
	constexpr static const char* literal = "18";

	template<int i>
	constexpr static char* Convert()
	{
		buffer[MAX - 1] = 0;
		SetDigit<i, buffer, MAX - 2>::doIt();
		return buffer;
	}
};




template<int i>
struct Prime_print
{
	Prime_print<i - 1> a;							// recursive (requires Prime_print<1> specialization)
	enum { pri = is_prime<i, i - 1>::pri };
	void f()
	{
#if 1
		//if constexpr (pri)
		//{
			static_assert(! pri, IntToStr::Convert<i>() );

			//D<i> d = CondNull<pri ? 1 : 0>::value;		// 1 ==> error, 0 ==> succeeds
		//}
#else
		//D<i> d = CondNull<pri ? 1 : 0>::value;
		D<i> d = 0;
#endif
		a.f();
	}
};

template<>
struct Prime_print<1>		// full specialization to end the loop
{
	enum { pri = 0 };		// why is this needed??
	void f()
	{
		D<1> d = 0;
	}
};

constexpr int const LAST = 18;

#if 1
void print_primes()
{
	char* res = IntToStr::Convert<17>();
	static_assert(true, "" /*IntToStr::literal*/);
	
	Prime_print<LAST> a;
	a.f();
}

#else
void print_primes()
{}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	Meta_ErwinUnruh.cpp
//
// summary:	Implements the first metaprogram created in C++ by erwin unruh 
////////////////////////////////////////////////////////////////////////////////////////////////////

//#ifdef INCLUDE_STDAFX_H
#include "stdafx.h"
//#endif

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



template<int i>
struct Prime_print
{
	Prime_print<i - 1> a;							// recursive (requires Prime_print<1> specialization)
	enum { pri = is_prime<i, i - 1>::pri };
	void f()
	{
#ifdef INCLUDE_INT_TO_STR
		IntToStr::Convert<i>();
		static_assert(! pri, Buffer );
#else
		//D<i> d = CondNull<pri ? 1 : 0>::value;		// 1 ==> error, 0 ==> succeeds
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

#ifdef INCLUDE_INT_TO_STR
#include "IntToStr.h"
#endif


constexpr int const LAST = 18;

#if 1
void print_primes()
{
#ifdef INCLUDE_INT_TO_STR
	IntToStr::Convert<17>();

	constexpr char* res = IntToStr::buffer;
	static_assert(false, Buffer);
#endif
	Prime_print<LAST> a;
	a.f();
}

#else
void print_primes()
{}
#endif

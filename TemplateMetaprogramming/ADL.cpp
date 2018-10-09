#include "stdafx.h"

using namespace std;

namespace N
{
	struct S
	{
		int i;
	};
	void f(S s)
	{
		cout << s.i << endl;
	}
	void g(S s)
	{
		cout << s.i << endl;
	}
	void h(int i)
	{
		cout << i << endl;
	}
}

struct Base
{
	void basef(N::S s)
	{

	}
};

struct D : Base
{
	void mf(N::S s)
	{

	}

	void g(N::S s)
	{
		basef(s);
		f(s);
		mf(s);
		//h(1);
	}
};

// ADL for friend declarations
namespace ADL_FriendDecl
{
	template<typename T>
	class C
	{
		friend void f() {}
		friend void f(C<T> const&) {}
	};

	void g(C<int>* p)
	{
		//f();	// is f() visible here? NO
		f(*p);	// is f(C<int> const&) visible here? YES
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Injected class names 
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ICN
{
	template<template<typename> class TT> class X
	{};

	template<typename T> class C
	{
	public:
		C* a;			// same as C<T>* a
	//		C<void>& b;		// cannot be defined (recursive definition)
	//		X<C> c;			// supposed to denote the template C because it has no template argument list, but it actually represents X<C<T>> which does not match X!
		X<ICN::C> d;		// ok ::C is not the injected class name ==> always denotes the template
	};


	void useC_X()
	{
		X<C> x_c;
		C<int> cint;
		decltype(cint.a) x;
		decltype(cint.d) y;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Current instantiation
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace CurrentInstantiation
{
	template<typename T> struct C
	{
		using Type = T;

		struct I
		{
			C* c;
			C<Type>* c2;
			I* i;

			struct M
			{
				I* ii;
				I anI;
			};
		};

		struct J
		{
			C* c;
			C<Type>* c2;
			I* i;		// unknown specialization
			J* j;
		} jj;

		I* i;
	};

	template<> struct C<int>::I
	{
		int counter;
	};

	void use()
	{
		C<int>::I c{ 4 };
		c.counter++;
		C<int> cc{};	/// HERE!!!!
		cc.i->counter--;

		C<long>::I i;
		i.c->jj.i;

	}
}

namespace RequiredUseOfTypename
{
#if 0 // original plenty of typenames
	template<typename T>
	struct S : typename X<T>::Base
	{
		S() : typename X<T>::Base(typename X<T>::Base(0)) {}

		typename X<T> f()
		{
			typename X<T>::C * p;
			X<T>::D * q;
		}

		typename X<int>::C * s;

		using Type = T;
		using OtherType = typename S<T>::Type;
	};
#else
	template<typename T>
	struct X
	{
		struct Base
		{};
	};

	template<>
	struct X<int>
	{
		struct C
		{};
	};

	template<typename T>
	struct S : X<T>::Base
	{
		S() : X<T>::Base(typename X<T>::Base(0)) {}

		X<T> f()
		{
			typename X<T>::C * p;
			typename X<T>::D * q;
		}

		X<int>::C * s;

		using Type = T;
		using OtherType = typename S<T>::Type;
	};

#endif

}
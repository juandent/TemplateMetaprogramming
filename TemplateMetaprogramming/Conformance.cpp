#include "stdafx.h"

namespace Lookup_members_in_dependent_base
{

	template <typename T>
	struct B {
		void f();
	};

	template <typename T>
	struct D : public B<T> // B is a dependent base because its type
						   // depends on the type of T.
	{
		// One possible fix is to uncomment the following line.
		// If this is a type, don't forget the 'typename' keyword.
		using B<T>::f;

		void g() {
			f(); // error C3861: 'f': identifier not found
				 // Another fix is to change it to 'this->f();'
		}
	};

	static void h() {
		D<int> d;
		d.g();
	}

}

namespace Initializing_multiple_members_of_union_in_member_initializer
{
	union U
	{
		U()
			: i(1)//, j(1) // error C3442: Initializing multiple members of
						 // union: 'U::i' and 'U::j'.
						 // Remove all but one of the initializations to fix.
		{}
		int i;
		int j;
	};
}

namespace Hidden_friend_name_lookup_rules
{
	// Example 1
	struct S {
		friend void f(S *) { int a = 5; };
	};
	// Uncomment this declaration to make the hidden friend visible:
	void f(S *); // This declaration makes the hidden friend visible

	using type = void(*)(S *);
	type p = &f; // error C2065: 'f': undeclared identifier.


	 // Example 2
	struct T {
		friend void h(T *) {};
	};
	void g() {
		// Using nullptr instead of T prevents argument dependent lookup in T
		//h(nullptr); // error C3861: 'h': identifier not found

		T *p = nullptr;
		h(p); // Hidden friend now found via argument-dependent lookup.
	}
}

namespace UseScopedEnumInArrayBounds
{
	enum class Color {
		Red, Green, Blue
	};

	int data[static_cast<size_t>(Color::Blue)]; // error C3411: 'Color' is not valid as the size
						   // of an array as it is not an integer type.
						   // Cast to type size_t or int to fix.
}

namespace UseOfATLAttributes
{
	// Example 1
	//[uuid("594382D9-44B0-461A-8DE3-E06A3E73C5EB")]
	class A {};

	// Fix for example 1
	class __declspec(uuid("594382D9-44B0-461A-8DE3-E06A3E73C5EB")) B {};

}


namespace AmbiguousConditionalOperatorsArguments
{
	// Example 1: class that provides conversion to and initialization from some type T
	struct A
	{
		A(int) {}
		operator int() const { return 10; };
	};

	extern bool cond = true;

	A a(42);
	// Accepted when /Zc:ternary or /permissive- is not used:
	//auto x = cond ? 7 : a; // A: permissive behavior prefers A(7) over (int)a
						   // Accepted always:
	auto y = cond ? 7 : int(a);
	auto z = cond ? A(7) : a;

	namespace ExceptionFromAbove
	{
		// Example 2: exception from the above
		struct MyString
		{
			MyString(const char* s = "") noexcept {};  // from char*
			operator const char* () const noexcept { return ""; }; //   to char*
		};

		extern bool cond = true;

		MyString s;
		// Using /std:c++14, /permissive- or /Zc:ternary behavior
		// is to prefer MyString("A") over (const char*)s
		// but under /std:c++17 this line causes error C2445:
		//auto x = cond ? "A" : s;
		// You can use a static_cast to resolve the ambiguity:
		auto y = cond ? "A" : static_cast<const char*>(s);
	}
	namespace UsingVoid
	{
		// Example 3: void arguments
		void myassert(const char* text, const char* file, int line) { return; };
		// Accepted when /Zc:ternary or /permissive- is not used:
#define ASSERT_A(ex) (void)((ex) ? 1 : myassert(#ex, __FILE__, __LINE__))
		// Accepted always:
#define ASSERT_B(ex) (void)((ex) ? void() : myassert(#ex, __FILE__, __LINE__))

		void testASSERTS()
		{
			int x = 2;
			//ASSERT_A(x);
			ASSERT_B(x);
		}
	}

	namespace ConditionalOperatorReturnTypesVary
	{
		bool cond = true;
		int count = 0;
		void seeDifferentResultTypes()
		{
			// Example 4: different result types 
			char  a = 'A';
			const char  b = 'B';
			decltype(auto) x = cond ? a : b; // char without, const char& with /Zc:ternary 
			const char(&z)[2] = count > 3 ? "A" : "B"; // const char* without /Zc:ternary
		}
	}
}

namespace TwoPhaseNameLookup
{
	// dependent base
	struct ZZ {
		void g() {}
	};

	template<typename T>
	struct D : T {
		using T::g;

		void f() {
			// The call to g was incorrectly allowed in VS2017:
			g();  // Now under /permissive-: C3861
				  // Possible fixes:
				  // this->g();
				  // T::g();
		}
	};

	int main()
	{
		D<ZZ> d;
		d.f();
		return 0;
	}
}
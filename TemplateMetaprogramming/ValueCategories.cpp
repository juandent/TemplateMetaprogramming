
#include <type_traits>
#include <iostream>

#define e   (g(Y()))

class Y {};

int&& g(Y const&);

void printValueCategories()
{
	using namespace std;
	int x;
	
	if constexpr (std::is_lvalue_reference_v<decltype((e))>)
	{
		cout << "expression is lvalue\n";
	}
	else if constexpr (is_rvalue_reference_v<decltype((e))>)
	{
		cout << "expression is xvalue\n";
	}
	else
	{
		cout << "expression is prvalue\n";
	}
}


class X {};


void f(const X& )	// accepts an expression of any value category
{
}

void f(X&&)			// accepts prvalues and xvalues only, but is a better match
{
}

void useValueCategories()
{
	X v;
	const X c;
	f(v);						// passes a modifiable lvalue to the first f()
	f(c);						// passes a non-modifiable lvalue to the first f()
	f(X{});						// passes a prvalue to second f()
	f(std::move(v));		// passes an xvalue to the second f()


	int x = 3;					// x is a variable not an lvalue, 3 is a prvalue
	int y = x;					// x is an lvalue converted to a prvalue
}

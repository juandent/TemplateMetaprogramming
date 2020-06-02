
#include <type_traits>
#include <iostream>

#define e   (f(X()))

class X {};

int&& f(X const&);

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

#include "stdafx.h"


void autoVarsInFor()
{
	char hello[] = "Hello!";

	char destination[8];


	for( auto source = hello, target = destination; *source; ++source, ++target )
	{
		*target = *source;
	}
}

using std::cout;

// void f(int x)
// {
// 	cout << "f(int)\n";
// }

void f(int& x)
{
	cout << "f(int&)\n";
}

void f(const int& x)
{
	cout << "f(const int&)\n";
}

void f(int&& x)
{
	cout << "f(int&&)\n";
}

void f(const int&& x)
{
	cout << "f(const int&&)\n";
}

int ret_int()
{
	return 77;
}

void usingOverloads()
{
	f(3);
	f(ret_int());
	int y = 0;
	f(y);
	const int z = 1000;
	f(z);

	int const x = 42;
	f(std::move(x));


	using namespace  std;

	string s;

	getline(cin, s);

	cout << s << endl;

}

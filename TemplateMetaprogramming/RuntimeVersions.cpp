#include "stdafx.h"

// Runtime versions of algorithms:

int fac(int f)
{
	if (f == 1)
		return 1;
	return f * fac(f - 1);
}


template<int* pInt, int Val>
struct A
{};

int number;

void useA()
{
	const int xx = 40;
	A<&number, 12> a;
	//A<&xx, xx> b;
}
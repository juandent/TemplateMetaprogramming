#include "stdafx.h"
#include "constexpr_functions.h"


constexpr long T = fibonacci(2);

void use_fibonacci()
{
	constexpr long t = fibonacci(15);
	constexpr long u = fibonacci(-1);
}
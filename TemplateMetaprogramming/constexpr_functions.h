#pragma once

constexpr long fibonacci(long n)
{
	//assert(n >= 0);
	return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}


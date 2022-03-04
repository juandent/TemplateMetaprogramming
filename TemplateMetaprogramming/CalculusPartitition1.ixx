module;

//import std.core;
#include <functional>

export module calculus:integral;

export namespace calculus
{
	double integrate(std::function<double(double)> f, double x)
	{
		return f(x);
	}
}

namespace calculus
{
	int absolute(int a)
	{
		return a < 0 ? -a : a;
	}
}


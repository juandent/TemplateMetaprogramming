//import std.core;
#include <functional>

export module calculus:derivative;


template<typename T>
struct A
{
	using TType = T;
	TType* p;
};



export double derivative(std::function<double(double,double)> d, double a, double b)
{

	auto l = []()->const int& { return 42; };
	auto& z = l();				 // int z
	auto p = l();

	auto n = typeid(l).name();
	auto nl = typeid(l()).name();

	//A<l()>::p = nullptr;

	std::function<const int& ()> F = []()->const int& 
	{
		//static int a = 34;
		return 42; 
	};
	auto&& x = F(); // Undefined behavior: the result of F() is a dangling reference

	auto y = F();

	auto zz = F();

	return d(a,b);
}

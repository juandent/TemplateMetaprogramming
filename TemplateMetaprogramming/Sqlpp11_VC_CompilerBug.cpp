#include "stdafx.h"

#include <cstddef>


template <size_t N, const char(&s)[N]>
struct X
{
	static constexpr size_t Size = N;
	static constexpr const char* Str = s;
};

struct A
{
	static constexpr const char _literal[] = "concat_";
	using Y = X<sizeof(_literal), _literal>;
	static constexpr size_t x = Y::Size;
	static constexpr const char* p = Y::Str;
};


namespace DanglingReference
{

	template <typename T> auto f1(T i_)
	{ // return a lambda with a dangling reference     
		// since i_ will go out of scope at the return of the function     
		auto lambda = [&] {return  i_ + 3; };
		return lambda;
	}

	int main() {
		// lambda: no dangling reference 
		// i exists     
		int i = 2;
		auto lambda = [&] {return  i + 3; };
		int a_ok = lambda(); // 2+3=5 

		int val = 2;
		// create a lambda with a dangling reference     
		auto lamda_missingRef = f1(val);

		// example of result: // 14621279 instead of 2+3=5 
		// i_ is out of scope     
		int a_missingRef = lamda_missingRef();

		return 0;
	}

}

void Test_literal()
{
	A a{};
	auto p = a.p;
	auto x = a.x;
	DanglingReference::main();
}

#include "stdafx.h"

using namespace std;

// perfect return

template<typename Callable, typename...Args>
decltype(auto) call(Callable op, Args&&...args)
{

	if constexpr (is_void_v<invoke_result_t<Callable, Args...>>)
	{
		op(forward<Args>(args)...);
		return;				// return is void
	}
	else
	{
		decltype(auto) ret{ op(forward<Args>(args)...) };

		return ret;
	}
}

void f5()
{
	cout << "f5\n";
}

int& f6(int& a)
{
	static int b = 1;
	++b;
	return a;
}

void useCall()
{
	call(f5);
	int x = 45;
	auto& ret = call(f6, x);
	++ret;
}

constexpr int foo(double d)
{
	return static_cast<int>(d);
}

template<typename T>
void bar(const T x)
{
	if constexpr (auto obj = foo(x); is_same_v<decltype(obj),T>)
	{
		cout << "foo(x) yields same type\n";
	}
	else
	{
		cout << "foo(x) yields different type\n";
	}
	constexpr auto c = 35.66;
	if constexpr (constexpr auto obj = foo(c); obj == 0)
	{
		cout << "foo(c) == 10\n";
	}
}

void useBar()
{
	
}
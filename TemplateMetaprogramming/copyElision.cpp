#include "stdafx.h"



class MyClass
{
public:
	// MyClass(const MyClass&) = delete;
	// MyClass(MyClass&&) = delete;
	
};

void foo( MyClass param)
{
	
}

MyClass bar()
{
	return MyClass{};
}


namespace CopyElision
{
	void main()
	{
		foo(MyClass{});
		MyClass x = bar();
		foo(bar());
	}
}


template<typename T, typename ...Args>
T create(Args&&... args)
{

	return T{ std::forward<Args>(args)... };
}

#include <atomic>


namespace CopyElision
{
	void useCreate()
	{
		int i = create<int>(42);
		auto up = create<std::unique_ptr<int>>(new int{ 42 });
		auto ai = create< std::atomic<int >> (42);
	}
}

class CopyOnly
{
public:
	CopyOnly() {}
	CopyOnly(int) {}
	CopyOnly(const CopyOnly&) = default;
	CopyOnly(CopyOnly&&) = delete;
};

CopyOnly ret()
{
	return CopyOnly{};
}

CopyOnly x = 42;




decltype(auto) f3()
{

	return CopyOnly{};
}

void call_f3()
{
	auto r = f3();
	auto&& s = f3();
	//auto& t = f3();
	decltype(auto) rr = f3();
	
}


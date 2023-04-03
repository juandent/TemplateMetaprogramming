#include <iostream>
#include <type_traits>



template<typename T>
requires std::is_array_v<T> || std::is_pointer_v<T>
struct S {};

template<typename T>
using Ref = T&;

template<typename T>
concept C = requires
{
	typename std::remove_pointer_t<T>::inner;	// required nested member name
	typename S<T>;								// required class template specialization
	typename Ref<T>;							// required alias template substitution
};


template<typename T>
requires C<T>
void do_work(T t)
{
	
}

class F
{
public:
	struct inner {};
};

void useReqTipos()
{
	F f;
	do_work(&f);
	int arr[3];
	S<decltype(arr)> s;
	
	//do_work(arr);
}


// { expression } noexcept(optional) return-type - requirement(optional);

template<typename T>
concept C2 = requires(T x)
{
	// the expression *x must be valid
	// AND the type T::inner must be valid
	// AND the result of *x must be convertible to T::inner
	{*x} -> std::convertible_to<typename T::inner>;

	// the expression x + 1 must be valid
	// AND std::same_as<decltype((x + 1)), int> must be satisfied
	// i.e., (x + 1) must be a prvalue of type int
	{x + 1} -> std::same_as<int>;

	// the expression x * 1 must be valid
	// AND its result must be convertible to T
	{x * 1} -> std::convertible_to<T>;
};


class M
{
	int val;
public:
	M(int x) : val{x} {}
	struct inner {};
	inner in;
	inner operator*()
	{
		return in;
	}

	friend int operator+(M m, int i)
	{
		return m.val + i;
	}
	friend M operator*(M m, int i)
	{
		return M(m.val * i);
	}
};

template<typename T>
requires C2<T>
struct X
{};


void useCompoundReq()
{
	M anM{3};
	auto star = *anM;
	auto plus = anM + 1;
	auto times = anM * 1;

	X<M> x;
	// X<int> y;	//  'X': the associated constraints are not satisfied
	constexpr bool b = std::same_as<decltype(anM + 1), int>;
}


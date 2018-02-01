#include "stdafx.h"

#include <iostream>
#include <typeinfo>
#include <type_traits>

template<typename T>
void f(T)
{
}

template<typename A>
void printParameterType(void(&)(A))
{
	std::cout << "Parameter type: " << typeid(A).name() << '\n';
	std::cout << "- is int:     " << std::is_same<A, int>::value << '\n';
	std::cout << "- is const:   " << std::is_const<A>::value << '\n';
	std::cout << "- is pointer: " << std::is_pointer<A>::value << '\n';
}

void PassByValue()
{
	printParameterType(f<int>);
	printParameterType(f<int const>);
	printParameterType(f<int[7]>);
	printParameterType(f<int(int)>);
}


template<typename T>
using RemoveCVT = std::remove_const<typename std::remove_volatile<T>::type>;


template<typename T>
struct DecayT : RemoveCVT<T>
{};

// boundless array
template<typename T>
struct DecayT<T[]>
{
	using type = T * ;
};

// bounded array
template<typename T, std::size_t N>
struct DecayT<T[N]>
{
	using type = T * ;
};

template<typename R, typename... Args>
struct DecayT<R(Args...)>
{
	using type = R(*)(Args...);
};

template<typename R, typename... Args>
struct DecayT<R(Args..., ...)>
{
	using type = R(*)(Args..., ...);
};



template<typename T>
void printDecayedType()
{
	using A = typename DecayT<T>::type;
	std::cout << "Parameter type: " << typeid(A).name() << '\n';
	std::cout << "- is int:     " << std::is_same<A, int>::value << '\n';
	std::cout << "- is const:   " << std::is_const<A>::value << '\n';
	std::cout << "- is pointer: " << std::is_pointer<A>::value << '\n';
}

void useDecayT()
{
	printDecayedType<int>();
	printDecayedType<int const>();
	printDecayedType<int[7]>();
	printDecayedType<int(int)>();
}

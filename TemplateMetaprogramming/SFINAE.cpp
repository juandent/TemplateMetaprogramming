#include "stdafx.h"

// import std_core;

template<typename T,  typename U = typename T::type >
constexpr bool has_type_member(T*)
{
	return true;
}

template<typename T>
constexpr bool has_type_member(...)
{
	return false;
}

template<typename T, typename Dummy = void>
struct HasTypeMember
{
	constexpr static bool has = false;
};

template<typename T>
struct HasTypeMember<T, typename T::type>
{
	constexpr static bool has = true;
};

float fun( float a, float b)
{
	return a * b;
}

struct AA
{
	using type = long;
};

void use()
{
	constexpr auto b = has_type_member<int>(0);
	constexpr auto bb = has_type_member<AA>(0);

	// fun(a=10.4, b = 3.7);

	// constexpr auto ih = HasTypeMember<int>::has;
	// constexpr auto ah = HasTypeMember<AA>::has;
}
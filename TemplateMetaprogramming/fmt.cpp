#include "stdafx.h"

#include <string_view>
#include <type_traits>

#define FAIL_CONSTEVAL throw

template<typename T>
struct Checker
{
	consteval Checker(const char* fmt)
	{
		if (fmt != std::string_view{ "valid" })
			throw;	// FAIL_CONSTEVAL;
		if (!std::is_same_v<T, int>)
			throw;	// FAIL_CONSTEVAL;
	}
};


template<typename T>
void fmt(std::type_identity_t<Checker<T>> checked, T) {}

// template<typename T>
// void fmt(Checker<T> checked, T);

void useChecker()
{
	fmt("valid", 10);
	// fmt("oops", 10);
	// fmt("valid", "foo");
}

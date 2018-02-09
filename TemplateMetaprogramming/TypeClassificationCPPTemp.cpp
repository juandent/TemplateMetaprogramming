#include "stdafx.h"




template<typename T, typename = std::void_t<>>
struct IsClassT : std::false_type
{
};

template<typename T>
struct IsClassT<T, std::void_t<int T::*>> : std::true_type
{
};


class AAA
{
	int val;
};

union UU
{
	int x;
	char y[sizeof(int)];
};

constexpr bool isClass = IsClassT<AAA>::value;

constexpr bool isIntAClass = IsClassT<int>::value;

constexpr bool isUnionAClass = IsClassT<UU>::value;

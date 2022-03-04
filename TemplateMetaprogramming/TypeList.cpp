#include "stdafx.h"


#define TYPELIST_1(T1)		TypeList<T1, NullType>
#define TYPELIST_2(T1,T2)	TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3)	TypeList<T1, TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4)	TypeList<T1, TYPELIST_3(T2,T3,T4)>





template<typename H, typename T>
struct TypeList
{
	using Head = H;
	using Tail = T;
};

struct NullType
{};


template<typename TList, typename T, typename U>
struct ReplaceAll;

template<typename T, typename U>
struct ReplaceAll<NullType, T, U>
{
	using Result = NullType;
};


template<typename T, typename Tail, typename U>
struct ReplaceAll<TypeList<T, Tail>, T, U>
{
	using Result = TypeList<U, typename ReplaceAll<Tail, T, U>::Result>;
};

template<typename Head, typename Tail, typename T, typename U>
struct ReplaceAll<TypeList<Head, Tail>, T, U>
{
	using Result = TypeList<Head, typename ReplaceAll<Tail, T, U>::Result>;
};


using SimpleIntegers = TYPELIST_4(char, long, char, int);

using CharToDouble = typename ReplaceAll<SimpleIntegers, char, double>::Result;


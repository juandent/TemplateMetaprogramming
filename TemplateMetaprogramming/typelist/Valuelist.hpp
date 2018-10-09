#pragma once

#include "isempty.hpp"
#include "ctvalue.hpp"
#include "typelist/typelistFront.hpp"
#include "typelist/typelistPopFront.hpp"
#include "typelist/typelistPushFront.hpp"
#include "typelist/typelistPushBack.hpp"

template<typename T, T...Values>
struct ValueList
{};

template<typename T, T...Values>
struct IsEmpty<ValueList<T, Values...>>
{
	static constexpr bool value = sizeof...(Values) == 0;
};

template<typename T, T Head,  T...Tail>
struct FrontT<ValueList<T, Head, Tail...>>
{
	using Type = CTValue<T, Head>;
	static constexpr T value = Head;
};

template<typename T, T Head, T...Tail>
struct PopFrontT<ValueList<T, Head, Tail...>>
{
	using Type = ValueList<T, Tail...>;
};

template<typename T, T ...Values,T New>
struct PushFrontT<ValueList<T, Values...>, CTValue<T, New>>
{
	using Type = ValueList<T, New, Values...>;
};

template<typename T, T ...Values, T New>
struct PushBackT<ValueList<T, Values...>, CTValue<T, New>>
{
	using Type = ValueList<T, Values..., New>;
};


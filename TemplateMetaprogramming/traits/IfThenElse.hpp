#pragma once

template<bool cond, typename TrueType, typename FalseType>
struct IfThenElseT {
	using Type = TrueType;
};

template<typename TrueType, typename FalseType>
struct IfThenElseT<false, TrueType, FalseType> {
	using Type = FalseType;
};

template<bool cond, typename TrueType, typename FalseType>
using IfThenElse = typename IfThenElseT<cond, TrueType, FalseType>::Type;


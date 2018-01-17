#pragma once

#include "UtilsForMyFold.h"

///////////////////////////////
// myReverseFold

template<typename Seq, typename Prev, template<typename P, typename H> class BinaryOp>
struct myReverseFold
{
	using type = typename BinaryOp<
		typename myReverseFold<tail_t<Seq>, Prev, BinaryOp>::type, head_t<Seq>>::type;
};

// specialized template (end of recursion)
template<typename Prev, template<typename P, typename H> typename BinaryOp>
struct myReverseFold<vector<>, Prev, BinaryOp>
{
	using type = Prev;
};


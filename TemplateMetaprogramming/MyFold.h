#pragma once

#include "UtilsForMyFold.h"

///////////////////////////////
// myFold: the good one!!!

template<typename Seq, typename Prev, template<typename P, typename H> class BinaryOp>
struct myFold
{
	using type = typename myFold<tail_t<Seq>,
		typename BinaryOp<Prev, head_t<Seq>>::type,
		BinaryOp>::type;
};

// specialized template (end of recursion)
template<typename Prev, template<typename P, typename H> typename BinaryOp>
struct myFold<vector<>, Prev, BinaryOp>
{
	using type = Prev;
};


#ifdef USE_SAMPLES
// sample sequence:
using MySeq = vector<long, float, short, double, float, long, long double>;


using xx = typename myFold<MySeq, vector<>, push_back_external>::type;
using at00 = get_by_pos<2, xx>::type;

using yy = typename myFold<MySeq, vector<>, push_front_external>::type;
#endif

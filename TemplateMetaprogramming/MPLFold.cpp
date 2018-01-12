#include "stdafx.h"


#include <boost\mpl\fold.hpp>
#include <boost\mpl\reverse_fold.hpp>
#include <boost\mpl\placeholders.hpp>
#include <boost\mpl\clear.hpp>
#include <boost\mpl\push_front.hpp>
#include <boost\mpl\vector.hpp>
#include <boost\mpl\equal.hpp>
#include <boost\type_traits\is_float.hpp>



namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;


// first as runtime code:

#include <deque>
#include <algorithm>

using sequence = std::deque<int>;


struct combine_back
{
	sequence operator()(sequence prev, int head)
	{
		sequence combined{ prev };
		combined.push_back(head);
		return combined;
	}
};

auto tail(sequence seq) -> sequence
{
	// skip the first element
	auto start = seq.begin();
	++start;
	sequence res{ start, seq.end() };
	return res;
}

auto head(const sequence& seq) -> int
{
	return seq[0];
}


template<typename BinaryOp>
auto fold(sequence seq, sequence prev, BinaryOp cf) -> sequence
{
	if (seq.empty())
	{
		return sequence{ prev };
	}
	else
	{
		return fold(tail(seq), cf(prev, head(seq)), cf);
	}
}

void doReverseAtRunTime()
{
	sequence v{ 3,8,99,45 };

	// initial type:
	sequence output{};

	auto res = fold<combine_back>(v, output, combine_back{});

}


template<typename Seq>
struct reverse : mpl::fold<
	Seq,
	typename mpl::clear<Seq>::type,		// initial type
	mpl::push_front<_,_>
>
{};


template<typename T>
struct Dummy {};

using seq = mpl::vector< int, double, long >;

using reverted = reverse<seq>::type;

constexpr bool equalToMe = mpl::equal<seq, seq>::value;

constexpr bool equal = mpl::equal<reverted, mpl::vector<long, double, int>>::value;




//////////////////////////////// fold sample from Boost's web page


using types = mpl::vector<long, float, short, double, float, long, long double>;

using number_of_floats = mpl::fold<
	types
	, mpl::int_<0>
	, mpl::if_< boost::is_float<_2>, mpl::next<_1>, _1 >
>::type;

static_assert(number_of_floats::value == 4, "");



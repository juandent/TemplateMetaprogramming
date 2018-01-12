#include "stdafx.h"

#include <boost\mpl\deref.hpp>
#include <boost\mpl\max_element.hpp>
#include <boost\mpl\replace.hpp>
#include <boost\mpl\less.hpp>
#include <boost\mpl\sizeof.hpp>
#include <boost\mpl\placeholders.hpp>
#include <boost\mpl\vector.hpp>
#include <boost\mpl\list.hpp>
#include <boost\mpl\front.hpp>
#include <boost\mpl\next.hpp>
#include <boost\mpl\copy.hpp>
#include <boost\mpl\vector_c.hpp>
#include <boost\mpl\transform.hpp>
#include <boost\mpl\at.hpp>
#include <boost\mpl\equal.hpp>


namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;


template<class Seq>
struct biggest_float_as_double
	: mpl::deref<
	typename mpl::max_element<
	typename mpl::replace<
	Seq,
	float,
	double>::type,
	mpl::less<mpl::sizeof_<_1>, mpl::sizeof_<_2>>>::type
	>
{};


//using aSet = mpl::set<char, float, double, float>;
using aVec = mpl::vector<char, float, double, float>;

using replaced = mpl::replace<aVec, float, double>::type;

using second = mpl::deref<mpl::next< mpl::begin<aVec>::type>::type>::type;

using first = mpl::deref<mpl::identity< mpl::begin<aVec>::type>::type>::type;

using res = biggest_float_as_double<aVec>::type;

/////////////////////////////////////////
// 6.3 inserters

struct A {};
struct B {};
struct C {};

using result_vec = mpl::copy<
	mpl::list<A, B, C>,
	mpl::back_inserter<mpl::vector<>>>::type;

using first_in_vec = mpl::deref<mpl::begin<result_vec>::type>::type;

constexpr bool equal1 = mpl::equal<result_vec, mpl::vector<A,B,C>>::value;


/////////////////////////////////
// transform

using S = mpl::vector<
	mpl::vector_c<int, 1, 2, 3>
	, mpl::vector_c<int, 4, 5, 6>
	, mpl::vector_c<int, 7, 8, 9>>::type;


using initial_state = mpl::int_<0>;

using sum = mpl::transform<
	S
	, mpl::front<_>
	, mpl::inserter<
	mpl::int_<0>
	, mpl::plus<_, _>>>::type;

constexpr auto res_sum = sum::value;

using fronts = mpl::transform<
	S
	, mpl::front<_>>::type;

constexpr bool equal = mpl::equal<fronts, mpl::vector<mpl::integral_c<int,1>, mpl::integral_c<int,4>, mpl::integral_c<int,7>>>::value;

using zero_fronts = mpl::at<fronts, mpl::int_<1>>::type;





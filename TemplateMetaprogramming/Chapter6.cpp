#include "stdafx.h"

#include "Chapter6.h"
#include <iostream>
#include <vector>
#include <boost/type_traits.hpp>
//#include <loki/Typelist.h>
#include <boost\mpl\vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/at.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/range_c.hpp>
#include <ratio>
//#include <boost\mpl\vector.hpp>
#include <boost\mpl/size.hpp>
#include <boost\mpl\order.hpp>
#include <boost\mpl\map.hpp>
#include <boost\mpl\pair.hpp>
#include <boost\mpl\key_type.hpp>
#include <boost\mpl\value_type.hpp>
#include <boost\mpl\set.hpp>
#include <boost\mpl\pop_back.hpp>
#include <boost\mpl\pop_front.hpp>
#include <boost\mpl\erase.hpp>
#include <boost\mpl\vector\vector10.hpp>
#include <boost\mpl\iterator_tags.hpp>
#include <boost\mpl\distance.hpp>
#include <boost\mpl\clear.hpp>
#include <boost\mpl\push_back.hpp>
#include <boost\mpl\front.hpp>
#include <boost\mpl\inserter.hpp>
#include <boost\mpl\back.hpp>

#include "Debug.h"

// Dimensions (pg 40 -- C++ Template Metaprogramming
namespace mpl = boost::mpl;
using namespace mpl::placeholders;
using namespace std;

typedef mpl::vector<
	mpl::vector_c<int, 1, 2, 3>,
	mpl::vector_c<int, 4, 5, 6>,
	mpl::vector_c<int, 7, 8, 9>
> S;

namespace Section6_3
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A second.
	/// 			We first need to have a template in order to create a lambda expression </summary>
	///
	/// <remarks>	Juan Dent, 23/3/2017. </remarks>
	///
	/// <typeparam name="Seq">	Type of the sequence. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Seq>
	struct second
	{
		typedef typename mpl::deref<
			typename mpl::next<
			typename mpl::begin<Seq>::type
			>::type
		>::type	type;
	};

	void useTransform()
	{
		typedef mpl::transform<
			S,					// input sequence
			mpl::front<_>,		// transformation selects front element from each vector element (??)
			mpl::inserter<
			mpl::int_<0>,		// results start with 0
			mpl::plus<_, _>		// and adds each output element
			>
		>::type sum;

		sum s;

		typedef typename mpl::begin<S>::type beg_iter;
		typedef typename mpl::next<beg_iter>::type	second_iter;
		typedef typename mpl::deref<second_iter>::type second_type;

		second_type sec;

		typedef second<_> second_lambda_expression;

		typedef mpl::transform<
			S,					// input sequence
			second_lambda_expression,		// transformation selects second element from each vector element (??)
			mpl::inserter<
			mpl::int_<0>,		// results start with 0
			mpl::plus<_, _>		// and adds each output element
			>
		>::type sum_second;
		sum_second sec_by_lambda;

		cout << "A" << endl;

		typedef mpl::transform<
			S,					// input sequence
			mpl::back<_>,		// transformation selects last element from each vector element (??)
			mpl::inserter<
			mpl::int_<0>,		// results start with 0
			mpl::plus<_, _>		// and adds each output element
			>
		>::type sum_b;

		sum_b sb;



	}

}
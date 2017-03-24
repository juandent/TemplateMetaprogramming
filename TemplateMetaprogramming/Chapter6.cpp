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
#include <boost\mpl\lambda.hpp>
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
#include <boost\mpl\protect.hpp>

#include "Debug.h"

// Dimensions (pg 40 -- C++ Template Metaprogramming
namespace mpl = boost::mpl;
using namespace mpl::placeholders;
using namespace std;


namespace Section6_3
{
	typedef mpl::vector<
		mpl::vector_c<int, 1, 2, 3>,
		mpl::vector_c<int, 4, 5, 6>,
		mpl::vector_c<int, 7, 8, 9>
	> S;

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

	typedef second<_> second_lambda_expression;

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

		typedef mpl::transform<
			S,					// input sequence
			mpl::front<_>		// unary operation to apply to each element of S
		>::type front_col;		// result: vector3<integral_c<int,1>, integral_c<int, 4>, integral_c<int, 7>> 

		front_col fc;


		typedef typename mpl::begin<S>::type beg_iter;
		typedef typename mpl::next<beg_iter>::type	second_iter;
		typedef typename mpl::deref<second_iter>::type second_type;

		second_type sec;

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



namespace LambdaMetaFunction
{
	// lambda: composition and argument binding http://www.boost.org/doc/libs/1_63_0/libs/mpl/doc/refmanual/lambda.html


	// If X is a Placeholder Expression, transforms X into a corresponding Metafunction Class, otherwise X is returned unchanged.

	template<typename Seq>
	struct second
	{
		typedef typename mpl::deref<
			typename mpl::next<
			typename mpl::begin<Seq>::type
			>::type
		>::type	type;
	};

	// template as lambda expression:
	typedef second<_> second_lambda_expression;

	typedef mpl::lambda<second_lambda_expression>::type f_as_metafn_class;



	/*
	If x is a Placeholder Expression in a general form X<a1, ...an>, where X is a class template and a1, ... an are arbitrary types, equivalent to

		typedef protect< bind<
		quoten<X>
		, lambda<a1>::type, ... lambda<an>::type
		> > f;

	otherwise, f is identical to x.
	*/

	template<typename N1, typename N2>
	struct int_plus : mpl::int_< (N1::value + N2::value)>
	{};

	typedef mpl::lambda < int_plus<_1, mpl::int_<42>>>::type f1;

	typedef mpl::bind< mpl::quote2<int_plus>, _1, mpl::int_<30>> f2;

	typedef f1::apply< mpl::int_<25>>::type r1;
	typedef f2::apply< mpl::int_<35>>::type r2;

	static_assert( r1::value == 67, "");
	static_assert(r2::value == 65, "");


	// mpl::protect
	
	// protect is an identity wrapper for a Metafunction Class that prevents its argument from being recognized as a bind expression.

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A f is a metafunction class (has nested template class apply with nested type </summary>
	///
	/// <remarks>	Juan Dent, 23/3/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	struct f
	{
		template<typename T1, typename T2>
		struct apply
		{
			typedef T2 type;
		};
	};

	typedef mpl::bind< mpl::quote3<mpl::if_>, _1, _2, mpl::bind<f, _1, _2>> b1;

	typedef mpl::bind< mpl::quote3<mpl::if_>, _1, _2, mpl::protect< mpl::bind<f, _1, _2>>> b2;

	typedef mpl::apply_wrap2<b1, mpl::false_, char>::type wr1;

	typedef mpl::apply_wrap2<b2, mpl::false_, char>::type wr2;

	static_assert(is_same<wr1, char>::value, "");

	static_assert(is_same < wr2, mpl::protect< mpl::bind<f, _1, _2>>>::value, "");

}
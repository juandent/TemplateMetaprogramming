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
#include <boost\mpl\quote.hpp>
#include <boost\mpl\apply_wrap.hpp>
#include <boost\mpl\list_c.hpp>

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


		typedef  mpl::begin<S>::type beg_iter;
		typedef  mpl::next<beg_iter>::type	second_iter;
		typedef  mpl::deref<second_iter>::type second_type;

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

	typedef mpl::lambda < int_plus<_1, mpl::int_<42>>>::type f0;

	typedef mpl::bind< mpl::quote2<int_plus>, _1, mpl::int_<30>> f2;

	typedef f0::apply< mpl::int_<25>>::type r1;
	typedef f2::apply< mpl::int_<35>>::type r2;

	static_assert( r1::value == 67, "");
	static_assert(r2::value == 65, "");

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	mpl::protect is an identity wrapper for a metafunction class that prevents 
	/// 			its argument to be recognized as a bind expression </summary>
	///
	///				
	/// 
	/// <remarks>	For any metafunction class f: 
	/// 			typedef mpl::protect<f> g;
	/// 			If f is a bind expression equivalent to:
	/// 			
	/// 			struct g
	/// 			{
	/// 				template< typename U1, ... typename Un>
	///					struct apply
	///						: apply_wrapn<f, U1, ... Un>
	///					{};
	/// 			};
	/// 			
	/// 			otherwise equivalent to typedef f g;
	/// 			
	/// 			Juan Dent, 24/3/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Example: A f is a metafunction class (has nested template class 
	/// 			apply with nested type </summary>
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

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Defines an alias representing the first b.
	/// 			(bind expression) </summary>
	///
	/// <remarks>	Juan Dent, 24/3/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef mpl::bind< mpl::quote3<mpl::if_>, _1, _2, mpl::bind<f, _1, _2>> b1;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Defines an alias representing the second b.
	/// 			(bind expression) </summary>
	///
	/// <remarks>	Juan Dent, 24/3/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef mpl::bind< mpl::quote3<mpl::if_>, _1, _2, mpl::protect< mpl::bind<f, _1, _2>>> b2;

	typedef mpl::apply_wrap2<b1, mpl::false_, unsigned>::type wr1;

	typedef mpl::apply_wrap2<b2, mpl::false_, long>::type wr2;

	static_assert(is_same<wr1, unsigned>::value, "");

	static_assert(is_same < wr2, mpl::protect< mpl::bind<f, _1, _2>>>::value, "");

	void useLambdaMetaFunction()
	{
		b1 bb;
		b2 bb2;
		wr1 w1;
		wr2 w2;

		cout << "end of function\n";
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Higher order primitive that wraps an n-ary metafunction to a 
	/// 			metafunction class: quoten. </summary>
	///
	/// <value>	mpl::quoten </value>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct f1
	{
		typedef T type;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	struct f5
	{
		// no type member
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Generating metafunction classes with mpl::quote </summary>
	///
	/// <remarks>	Juan Dent, 24/3/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef mpl::quote1<f1>::apply<int>::type t1;

	typedef mpl::quote5<f5>::apply<char, short, int, long, long long>::type t5;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: bind
//
// summary:	bind is a higher - order primitive for Metafunction Class composition and argument binding.
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace bind
{
	struct f1
	{
		template<typename U1> struct apply
		{
			typedef U1 type;
		};
	};

	struct f5
	{
		template<typename U1, typename U2, typename U3, typename U4, typename U5>
		struct apply
		{
			typedef U5 type;
		};
	};

	typedef  f1::template apply<char>::type f1_invoked_with_template;
	typedef  f1::apply<char>::type			f1_invoked;

	static_assert(is_same<f1_invoked, f1_invoked_with_template>::value, "");

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	in this case, f or ak is a bind expression. </summary>
	///
	/// <remarks>	Juan Dent, 24/3/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef mpl::apply_wrap1< mpl::bind1<f1, _1>, int>::type r11;
	typedef mpl::apply_wrap5< mpl::bind1<f1, _5>, void, void, void, void, int>::type r12;

	static_assert(is_same<r11, int>::value, "");
	static_assert(is_same<r12, int>::value, "");

	typedef mpl::apply_wrap5< mpl::bind5<f5, _1, _2, _3, _4, _5>, void, void, void, void, int>::type r51;
	typedef mpl::apply_wrap5< mpl::bind5<f5, _5, _4, _3, _2, _1>, int, void, void, void, void>::type r52;

	static_assert(is_same<r51, int>::value, "");
	static_assert(is_same<r52, int>::value, "");

}


namespace reverse_fold
{
	typedef mpl::list_c<int, 5, -1, 0, -7, -2, 0, -5, 4>		numbers;
	typedef mpl::list_c<int, -1, -7, -2, -5>					negatives;

	typedef mpl::reverse_fold<
		numbers,
		mpl::list_c<int>,
		mpl::if_< 
		mpl::less< _2, mpl::int_<0>>, 
		mpl::push_front<_1, _2>,
		_1>
	>::type result;

	static_assert(mpl::equal<negatives, result>::value, "");

	typedef mpl::reverse_fold <
		numbers,
		mpl::list_c<int>,
		mpl::if_<
		mpl::less< _2, mpl::int_<0>>,
		mpl::push_front<_1, _2>,
		_1>,
		mpl::push_front<_1,_2>
	>::type result_both;

	typedef mpl::vector_c<int, 1, 2, 3, 4, 5> integers;

	typedef mpl::list_c<int, 3, 5, 7>			odds;

	typedef mpl::reverse_fold<
		integers,
		mpl::fold<odds, mpl::vector<>, mpl::push_back<_1,_2>>::type,
		mpl::push_back<_1,_2>
	>::type t;

#if 1	// NOT OK
	typedef mpl::reverse_fold< 
		integers, 
		mpl::vector<>,
		mpl::push_front<_1, _2>,
		mpl::push_front<odds,_2>	
	>::type t_equivalent;
#endif

	void useReverseFold()
	{
		result_both res;
		t at;
		t_equivalent otherT;

		cout << "end\n";
	}
	// static_assert(mpl::equal<negatives, result>::value, "");

}
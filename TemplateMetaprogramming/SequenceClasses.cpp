#include "stdafx.h"

///#include "exercise_3_1.hpp"
#include "AssociativeSequences.h"
#include <iostream>
#include <vector>
#include <boost/type_traits.hpp>
//#include <loki/Typelist.h>
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

#include "Debug.h"

// Dimensions (pg 40 -- C++ Template Metaprogramming
namespace mpl = boost::mpl;
using namespace mpl::placeholders;
using namespace std;


namespace SequenceClasses {
	namespace vector {
		void vectorLimits()
		{
			typedef mpl::vector9<
				int[1], int[2], int[3], int[4], int[5], int[6], int[7], int[8], int[9]
			> s9;
			typedef mpl::push_back<s9, int[10]>::type s10;	// ok
			typedef mpl::push_back<s10, int[11]>::type s11;

		}
} }


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: SampleSequence
//
// summary:	Section 5.11 pg 97; C++ Template Metaprogramming.
////////////////////////////////////////////////////////////////////////////////////////////////////

	struct none {};

#ifdef NO_TAG
		template<typename T0 = none, typename T1 = none, typename T2 = none>
		struct tiny
		{
			typedef tiny type;
			typedef T0 t0;
			typedef T1 t1;
			typedef T2 t2;
		};
	}

#else
	struct tiny_tag {};

	template<typename T0 = none, typename T1 = none, typename T2 = none>
	struct tiny
	{
		typedef tiny_tag	tag;
		typedef tiny		type;
		typedef T0			t0;
		typedef T1			t1;
		typedef T2			t2;
	};
#endif

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Manipulate a tiny. </summary>
	///
	/// <remarks>	Juan Dent, 21/3/2017. Very simple due to tiny's straightforward definition</remarks>
	///
	/// <typeparam name="Tiny">	Type of the tiny. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Tiny>
	struct manipulate_tiny
	{
		typedef typename Tiny::t0 t0;
		// ...
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A tiny iterator. </summary>
	///
	/// <remarks>	Juan Dent, 21/3/2017.
	/// 			We do not place next and prev as part of the iterator in order to avoid the
	/// 			blob anti-pattern </remarks>
	///
	/// <typeparam name="Tiny">	Type of the tiny. </typeparam>
	/// <typeparam name="Pos"> 	Type of the position (integral wrapper). </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Tiny, typename Pos>
	struct tiny_iterator
	{
		typedef mpl::random_access_iterator_tag category;
		typedef tiny_iterator	type;

		// More OO design - yet it fails to make each metafunction serve one goal well and only one
		// not good idea:
		// TODO: test these!!
		// Actually, the state of this struct is NOT changed by either of the following metafunctions!
		// So, there is no compelling reason from OO philosophy to nest them here complicating this 
		// struct unnecessarily...
		typedef typename mpl::next<Pos>::type next;
		typedef typename mpl::prior<Pos>::type prior;

	};

	template<typename Tiny, typename Pos>
	struct mpl::next<tiny_iterator<Tiny, Pos>>
	{
		typedef tiny_iterator <
			Tiny,
			typename mpl::next<Pos>::type
		> type;
	};

	template<typename Tiny, typename Pos>
	struct mpl::prior<tiny_iterator<Tiny, Pos>>
	{
		typedef tiny_iterator <
			Tiny,
			typename mpl::prior<Pos>::type
		> type;
	};

	template<typename Tiny, size_t N>
	struct tiny_at;

	// partially specialized accessors for each index
	template<typename Tiny>
	struct tiny_at<Tiny, 0>
	{
		typedef typename Tiny::t0	type;
	};

	template<typename Tiny>
	struct tiny_at<Tiny, 1>
	{
		typedef typename Tiny::t1	type;
	};

	template<typename Tiny>
	struct tiny_at<Tiny, 2>
	{
		typedef typename Tiny::t2	type;
	};

	// partialy specialize mpl::at for tiny sequences:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	An at. </summary>
	///
	/// <remarks>	Juan Dent, 21/3/2017. </remarks>
	///
	/// <typeparam name="T0"> 	Generic type parameter. </typeparam>
	/// <typeparam name="T1"> 	Generic type parameter. </typeparam>
	/// <typeparam name="T2"> 	Generic type parameter. </typeparam>
	/// <typeparam name="Pos">	Type of the position (Integral wrapper). </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SPECIALIZING_AT

	template<typename T0, typename T1, typename T2, typename Pos>
	struct mpl::at<tiny<T0, T1, T2>, Pos> 
		: tiny_at<tiny<T0, T1, T2>, Pos::value>
	{
	};
#endif

#ifdef DEFINE_INSIDE_NAMESPACES_EXPLICITLY

namespace boost { namespace mpl {

#ifndef NO_TAG
		template<>
		struct at_impl<tiny_tag>
		{
			template<typename Tiny, typename N>
			struct apply : tiny_at<Tiny, N::value>
			{};
		};

#if 0
		template<typename Sequence, typename N>
		struct at
			: at_impl<typename Sequence::tag>
			::template apply<Sequence, N>
		{};
#endif
#endif
		
		// now deref iterator
		template<typename Tiny, typename Pos>
		struct deref< tiny_iterator<Tiny, Pos>> : at<Tiny, Pos>
		{};
	}
}

#else

#define DEFINE_WITH_QUALIFIED_NAMESPACE_BUT_AT_GLOBAL_SCOPE
#ifdef DEFINE_WITH_QUALIFIED_NAMESPACE_BUT_AT_GLOBAL_SCOPE

#ifndef NO_TAG
	template<>
	struct mpl::at_impl<tiny_tag>
	{
		template<typename Tiny, typename N>
		struct apply : tiny_at<Tiny, N::value>
		{};
	};

#if 0
	template<typename Sequence, typename N>
	struct at
		: at_impl<typename Sequence::tag>
		::template apply<Sequence, N>
	{};
#endif
#endif

	// now deref iterator
	template<typename Tiny, typename Pos>
	struct mpl::deref< tiny_iterator<Tiny, Pos>> : at<Tiny, Pos>
	{};
#else		// DEFINE_WITH_QUALIFIED_NAMESPACE_BUT_AT_ANOTHER_NAMESPACE_SCOPE

	namespace Foo
	{
#ifndef NO_TAG
		template<>
		struct mpl::at_impl<tiny_tag>				// specialization not allowed in this namespace Foo
		{
			template<typename Tiny, typename N>
			struct apply : tiny_at<Tiny, N::value>
			{};
		};

#if 0
		template<typename Sequence, typename N>
		struct at
			: at_impl<typename Sequence::tag>
			::template apply<Sequence, N>
		{};
#endif
#endif

		// now deref iterator
		template<typename Tiny, typename Pos>
		struct ::mpl::deref< tiny_iterator<Tiny, Pos>> : at<Tiny, Pos>
		{};

	}
#endif
#endif

// advance

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An advance. </summary>
///
/// <remarks>	Juan Dent, 21/3/2017. </remarks>
///
/// <typeparam name="Tiny">	Type of the tiny. </typeparam>
/// <typeparam name="Pos"> 	Type of the position (integral wrapper). </typeparam>
/// <typeparam name="N">   	Type of the n. (integral wrapper)</typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename Tiny, typename Pos, typename N>
struct mpl::advance< tiny_iterator<Tiny, Pos>, N>
{
	typedef tiny_iterator<
		Tiny,
		typename mpl::plus<Pos, N>::type		// metafunction for adding integral wrappers
	>	type;
};

template<typename Tiny, typename Pos1, typename Pos2>
struct mpl::distance < tiny_iterator<Tiny, Pos1>, tiny_iterator<Tiny, Pos2>> : mpl::minus<Pos2, Pos1>
{};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A begin implementation - returns iterator to first element of sequence </summary>
///
/// <remarks>	Juan Dent, 23/3/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
struct mpl::begin_impl<tiny_tag>
{
	template<typename Tiny>
	struct apply
	{
		typedef tiny_iterator<Tiny, mpl::int_<0>> type;
	};
};

#define RETURNING_ITERATORS
#ifdef RETURNING_ITERATORS

#ifdef USE_LOG_N_IMPLEMENTATION

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An end implementation.
/// 			Using eval_if
/// 			Complexity is O(N), where N is number of types in sequence Tiny </summary>
///
/// <remarks>	Juan Dent, 23/3/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
struct mpl::end_impl<tiny_tag>
{
	// count how many none elements
	template<typename Tiny>
	struct apply  :  
		mpl::eval_if<is_same<none, typename Tiny::t0>, 
		tiny_iterator<Tiny, mpl::int_<0>>,
		mpl::eval_if<is_same<none, typename Tiny::t1>,
		tiny_iterator<Tiny, mpl::int_<1>>,
		mpl::eval_if<is_same<none, typename Tiny::t2>,
		tiny_iterator<Tiny, mpl::int_<2>>,
		tiny_iterator<Tiny, mpl::int_<3>>
		>
		>
		>
	{};
};

#else

template<typename T0, typename T1, typename T2>
struct tiny_size;

#define INHERITING_TYPE_FROM_INT_
#ifdef INHERITING_TYPE_FROM_INT_

template<>
struct tiny_size<none, none, none> 
	: mpl::int_<0>
{};

template<typename T0>
struct tiny_size<T0, none, none>
	: mpl::int_<1>
{};

template <typename T0, typename T1>
struct tiny_size<T0, T1, none>
	: mpl::int_<2>
{};

template<typename T0, typename T1, typename T2>
struct tiny_size 
	: mpl::int_<3>
{};

#else	// SPECIFYING type inside struct

template<>
struct tiny_size<none, none, none>
{
	typedef mpl::int_<0> type;
};

template<typename T0>
struct tiny_size<T0, none, none>
{
	typedef mpl::int_<1> type;
};

template <typename T0, typename T1>
struct tiny_size<T0, T1, none>
{
	typedef mpl::int_<2> type;
};

template<typename T0, typename T1, typename T2>
struct tiny_size
{
	typedef mpl::int_<3> type;
};

#endif

template<>
struct mpl::end_impl<tiny_tag>
{
	template<typename Tiny>
	struct apply
	{
		typedef tiny_iterator < 
			Tiny,
			typename tiny_size<
			typename Tiny::t0, 
			typename Tiny::t1, 
			typename Tiny::t2
			>::type
			>	type;
	};
};

#endif

#else		// ERROR!!

template<>
struct mpl::end_impl<tiny_tag>
{
	// count how many none elements
	template<typename Tiny>
	struct apply :
		mpl::eval_if<is_same<none, typename Tiny::t0>,
		mpl::int_<0>,
		mpl::eval_if<is_same<none, typename Tiny::t1>,
		mpl::int_<1>,
		mpl::eval_if<is_same<none, typename Tiny::t2>,
		mpl::int_<2>,
		mpl::int_<3>
		>
		>
		>
	{};
};


#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: TinySequenceImplementation
//
// summary:	Operations defined on tiny sequence.
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
advance
distance
next
prior
deref
at
begin
end
*/

namespace TinySequenceImplementation
{
	void useTiny()
	{
		typedef tiny<int, char*, long> t1;

		typedef mpl::at<t1, mpl::int_<0>>::type first;		// int
		first f = 9;

		typedef tiny_iterator<t1, mpl::int_<0>>	iter;
		iter it;

		typedef typename mpl::next<iter>::type ff;
		ff anf;

		typedef typename mpl::deref<iter>::type deref_t;
		deref_t dt;
		
		typedef typename mpl::begin<t1>::type  begin;

		typedef typename mpl::end<t1>::type  end;;

		typedef typename mpl::advance<end, mpl::int_<-1>>::type last;
		typedef typename mpl::deref<last>::type last_value_type;
		last_value_type lvalue;

		typedef typename mpl::distance<end, begin>::type dist;
		dist d;
		
		cout << f << endl;
	}
}
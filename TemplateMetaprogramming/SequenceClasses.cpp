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
#include <boost\mpl\clear.hpp>
#include <boost\mpl\push_back.hpp>
#include <boost\mpl\times.hpp>
#include <boost\mpl\push_back.hpp>

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
	}
}


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

	static_assert(Pos::value < 3 && Pos::value >= 0);

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

namespace boost {
	namespace mpl {

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

#if 1
template<typename Sequence, typename N>
struct at
	: mpl::at_impl<typename Sequence::tag>
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
	typedef typename tiny_iterator<
		Tiny,
		typename mpl::plus<Pos, N>::type		// metafunction for adding integral wrappers
	>::type	type;
	// this should be in tiny_iterator:
	static_assert(Pos::value < 4 && Pos::value >= 0);

	//typedef typename mpl::advance<tiny_iterator<Tiny, mpl::int_<5>>, mpl::int_<2>>::type seven;
	//typedef typename tiny_iterator<Tiny, mpl::int_<5>>::type fifth;

	// test position of final iterator
private:
	static constexpr int final_pos = mpl::plus<Pos, N>::value;
	static_assert(final_pos < 4 && final_pos >= 0);

};

template<typename Tiny, typename Pos1, typename Pos2>
struct mpl::distance < tiny_iterator<Tiny, Pos1>, tiny_iterator<Tiny, Pos2>> : mpl::minus<Pos2, Pos1>
{
private:

};

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
	struct apply :
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


template<typename Tiny>
struct tiny_size_composite
	: tiny_size< typename Tiny::t0, typename Tiny::t1, typename Tiny::t2>
{};


void tryComposite()
{
	typedef tiny<int, int, int> three_ints;
	auto size = tiny_size_composite<three_ints>::value;

}

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

//#define SLEEK_DESIGN
#ifdef SLEEK_DESIGN

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

#else

// more manual (less elegant) end_impl:

template<>
struct mpl::end_impl<tiny_tag>
{
	// count how many none elements
	template<typename Tiny>
	struct apply {

		// get constant wrapper:
		typedef mpl::eval_if<
			is_same<none, typename Tiny::t0>,	// if
			int_<0>,							// then
			mpl::eval_if<						// else
			is_same<none, typename Tiny::t1>,	// if
			int_<1>,							// then
			mpl::eval_if<						// else
			is_same<none, typename Tiny::t2>,	// if
			int_<2>,							// then
			int_<3>								// else
			>
			>
		>	value_wrapper;
		typedef tiny_iterator<Tiny, value_wrapper> type;

	};
};

#endif

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


template<>
struct mpl::clear_impl<tiny_tag>
{
	template<typename Tiny>
	struct apply : tiny<>
	{};
};

template<>
struct mpl::push_front_impl<tiny_tag>
{
	template<typename Tiny, typename T>
	struct apply : tiny<T, typename Tiny::t0, typename Tiny::t1>
	{
		static_assert(tiny_size<typename Tiny::t0, typename Tiny::t1, typename Tiny::t2>::value < 3, "tiny must have space left for push_front");
	};
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A push back primitive. Constant time complexity! </summary>
///
/// <remarks>	Juan Dent, 23/3/2017. </remarks>
///
/// <typeparam name="Tiny">	Type of the tiny. </typeparam>
/// <typeparam name="T">   	Generic type parameter. </typeparam>
/// <typeparam name="N">   	Type of the n. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////

template< typename Tiny, typename T, typename N>
struct push_back_primitive
{
	static_assert(N::value < 3, "cannot push_back on a full tiny sequence");
};


template< typename Tiny, typename T>
struct push_back_primitive<Tiny, T, mpl::int_<0>>
{
	typedef tiny<T>	type;
};

template< typename Tiny, typename T>
struct push_back_primitive<Tiny, T, mpl::int_<1>>
{
	typedef tiny<typename Tiny::t0, T>	type;
};

template< typename Tiny, typename T>
struct push_back_primitive<Tiny, T, mpl::int_<2>>
{
	typedef tiny<typename Tiny::t0, typename Tiny::t1, T>	type;
};

template<>
struct mpl::push_back_impl<tiny_tag>
{
	template<typename Tiny, typename T>
	struct apply
		: push_back_primitive<Tiny, T, typename tiny_size_composite<Tiny>::type>
	{};
};


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
push_back
push_front
tiny_size_composite
*/

namespace TinySequenceImplementation
{
	template < template<typename...> typename List, typename... T >
	constexpr typename std::enable_if< (sizeof...(T) <= 3), bool >::type
		is_valid_tiny() { return true; }

	template < template<typename...> typename List, typename... T >
	constexpr typename std::enable_if< (sizeof...(T) > 3), bool >::type
		is_valid_tiny() { return false; }

	void testTiny()
	{
		// define four tiny sequences and test tiny_size_composite!
		typedef tiny<> empty;
		static_assert(tiny_size_composite<empty>::value == 0);
		typedef tiny<int> one;
		static_assert(tiny_size_composite<one>::value == 1);
		typedef tiny<long, char*> two;
		static_assert(tiny_size_composite<two>::value == 2);
		typedef tiny<long, unsigned long, long[3]> three;
		static_assert(tiny_size_composite<three>::value == 3);

		// must have less than 3 parameters!!
		static_assert(is_valid_tiny<tiny, int, int, int, int>() == false);
		static_assert(is_valid_tiny<tiny, int, int, int>() == true);

#if 0
		template < typename... T >
		constexpr typename std::enable_if< (sizeof...(T) <= 3), bool >::type
			is_tiny(tiny<T...>) { return true; }

		template < typename... T >
		constexpr typename std::enable_if< (sizeof...(T) > 3), bool >::type
			is_tiny(tiny<T...>) { return false; }

		static_assert(is_valid_tiny<tiny<char, char, char, char>>() == false);
		typedef tiny<char*, char, char, char> four;
#endif
		// test at:
		typedef mpl::at<two, mpl::int_<1>>::type two_at_1;
		static_assert(is_same<two_at_1, char*>::value);
		// test begin and deref
		typedef mpl::begin<three>::type begin_iter;
		typedef mpl::deref<begin_iter>::type three_at_0;
		static_assert(is_same<three_at_0, long>::value);
		// .....
	}
	void useTiny()
	{
		typedef tiny<int, char*, long> t1;

		typedef mpl::at<t1, mpl::int_<0>>::type first;		// int
		first f = 9;

		typedef tiny_iterator<t1, mpl::int_<0>>	iter;
		iter it;

		typedef mpl::next<iter>::type ff;
		ff anf;

		typedef mpl::deref<iter>::type deref_t;
		deref_t dt;

		typedef  mpl::begin<t1>::type  begin;

		typedef  mpl::end<t1>::type  end;

		typedef  mpl::advance<end, mpl::int_<-1>>::type last;
		typedef  mpl::deref<last>::type last_value_type;
		last_value_type lvalue;

		typedef  mpl::distance<end, begin>::type dist;
		dist d;

#ifdef WATCH_ERROR
		typedef typename mpl::push_front<t1, double>::type new_t1;
		new_t1 tt1;
#endif

		typedef tiny<double, unsigned char[]> t2;

		cout << tiny_size_composite<t2>::value << endl;

		typedef  mpl::push_front<t2, long>::type new_t2;
		new_t2 tt2;

		typedef tiny<unsigned char[]> t3;

		typedef  mpl::push_back<t3, long long>::type new_t3;
		new_t3 tt3;

		typedef  mpl::push_back<new_t3, unsigned long>::type new_t4;
		new_t4 tt4;

		//#define WATCH_ERROR
#ifdef WATCH_ERROR
		typedef typename mpl::push_back<new_t4, unsigned long>::type new_t5;
		new_t5 tt5;
#endif

		cout << f << endl;
	}
}


namespace Chapter5_exercises
{
#if 1
	// exercise 5.1
	namespace impl
	{
		template<typename IntegralWrapper, size_t Pos, int Size, typename ElementType>
		struct wrapped_value
		{
			static constexpr ElementType multiply_factor = (2 * (Pos + 1) <= Size) ? 2 : 1;
			static constexpr ElementType orig_value = IntegralWrapper::value;
			static constexpr ElementType resulting_value = multiply_factor*orig_value;

			typedef mpl::integral_c<ElementType, resulting_value> type;
		};

		template<typename RASequence, size_t Pos, int Size>
		struct add_element
		{
			typedef typename std::remove_const< decltype(mpl::at<RASequence, mpl::int_<0>>::type::value)>::type	ElementType;

			typedef typename mpl::int_<Pos>::type PosWrapper;
			typedef typename mpl::at<RASequence, PosWrapper>::type original_element;
			typedef typename wrapped_value<original_element, Pos, Size, ElementType>::type current_element;
			typedef typename add_element<RASequence, Pos-1, Size>::output_sequence	previous_sequence;
			typedef typename mpl::push_back<previous_sequence, current_element>::type output_sequence;
		};

		template<typename RASequence, int Size>
		struct add_element<RASequence, 0,Size>
		{
			typedef typename std::remove_const< decltype(mpl::at<RASequence, mpl::int_<0>>::type::value)>::type	ElementType;

			typedef typename mpl::int_<0>::type PosWrapper;
			typedef typename mpl::at<RASequence, PosWrapper>::type original_element;

			typedef typename wrapped_value<original_element, 0, Size, ElementType>::type current_element;
			typedef typename mpl::clear<RASequence>::type	empty_sequence;
			typedef typename mpl::push_back<empty_sequence, current_element>::type output_sequence;
		};

	}

	// USE THIS:
	typedef mpl::vector_c<int, 1, 1, 2, 3, 5, 8, 13, 21, 34> fibonacci;
	typedef mpl::push_back<fibonacci, mpl::int_<55> >::type fibonacci2;
	//

	template< typename RASequence>
	struct double_first_half
	{
		static constexpr size_t Size = mpl::size<RASequence>::value;
		typedef typename impl::add_element<RASequence, Size - 1, Size>::output_sequence	type;
	};

#endif
	//template< typename RASequence, int Pos, int Size>


	void exercise5_1()
	{
		typedef mpl::vector2_c<long, 3, 5>::type orig_RASequence;	// of integral constant wrappers: models *vector_c* (not list_c, set_c)

#if 0 // all these are ok
		typedef typename mpl::at<orig_RASequence, mpl::int_<0>>::type zero;
		typedef impl::wrapped_value<zero, 0, 2, long>::type	zero_result;
		static_assert(zero_result::value == 6);
		typedef typename mpl::at<orig_RASequence, mpl::int_<1>>::type one;
		typedef impl::wrapped_value<one, 1, 2, long>::type	one_result;
		static_assert(one_result::value == 5);
#endif
		// empty sequence and push_back
		typedef mpl::vector_c<int, 1, 1, 2, 3, 5, 8, 13, 21, 34> fibonacci;
		typedef mpl::at<fibonacci, mpl::int_<1>>::type	second_element;
		//typedef mpl::times<second_element, mpl::int_<2>> doubled_element;
		constexpr int value = second_element::value * 2;
		typedef mpl::integral_c<int, value>	doubled_element;
		typedef mpl::clear<fibonacci>::type empty;
		typedef typename mpl::push_back<empty, doubled_element >::type fibonacci2;

		typedef mpl::at<fibonacci2, mpl::int_<0>>::type	orig_second_element_accessed;
		constexpr bool equal = std::is_same<doubled_element, orig_second_element_accessed>::value;
		static_assert(equal);	// !!

		typedef std::remove_const< decltype(mpl::at<fibonacci, mpl::int_<0>>::type::value)>::type	ElementType;


		typedef mpl::at<fibonacci2, mpl::int_<1>>::type	conv_second_element_accessed;
	


#if 0
		typedef mpl::vector_c<int, 3, 8, 12, 33>	RASequence;
		
		typedef double_first_half<RASequence>::type	ChangedSequence;

		constexpr static auto element_at_0 = mpl::at<RASequence, mpl::int_<0>>::type::value;
		typedef decltype(element_at_0)	ElementType;

		//const size_t zeroth = 
		typedef	mpl::at<RASequence, mpl::int_<0>>::type orig_zero;

		typedef	mpl::at<ChangedSequence, mpl::int_<0>>::type zeroth;

		constexpr bool same = std::is_same<zeroth, typename mpl::integral_c<int, 6>::type>::value;

		typedef	mpl::at<ChangedSequence, mpl::int_<1>>::type oneth;
		typedef	mpl::at<ChangedSequence, mpl::int_<2>>::type secondth;
		typedef	mpl::at<ChangedSequence, mpl::int_<3>>::type thirdth;
#endif

		//static_assert(mpl::equal<ChangedSequence, mpl::vector_c<int, 6, 16, 12, 33>>::type::value == true);

		//typedef double_first_half<orig_RASequence, 2> doubled_sequence;

		//typedef typename double_wrapped_value<mpl::int_<2>>::type  wrapped_double_value;
	}
}
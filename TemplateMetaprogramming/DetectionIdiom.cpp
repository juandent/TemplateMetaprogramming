#include "stdafx.h"

#include <type_traits>

using std::void_t;
using std::declval;
using std::false_type;
using std::true_type;


/***************************************************************/
// no nested apply member:
template<typename T, typename = void_t<>>
struct has_apply_member : false_type {};

//template<typename T>
//struct has_apply_member<T, void_t< typename T::apply> > : true_type {};

template<typename T>
struct has_apply_member<T, void_t< typename T::template apply<T>> > : true_type {};


/****************************************************************/



/*********************************************************************/
// primary template handles all types not supporting the operation:
template< class, template<class> class, class = void_t< > >
struct detect : false_type{};

 // specialization recognizes/validates only types supporting the archetype:
template< class T, template<class> class Op >
struct detect< T, Op, void_t<Op<T>> > : true_type { };

/***********************************************************************/


/***********************************************************************/
// archetypal expression for assignment operation:
template< class T >
using assign_t = decltype(declval<T&>() = declval<T const &>());

// trait corresponding to that archetype:
template< class T >
using is_assignable = detect<void, assign_t, T>;

/***********************************************************************/

namespace DetectionIdiom
{
	struct A
	{
		template<typename U>
		struct apply
		{};
	};

	struct B
	{
		int apply;
	};

	constexpr bool _has_apply = has_apply_member<A>::value;
	
	//A::apply
}

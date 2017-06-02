#include "stdafx.h"

#include <boost/mpl/if.hpp>
#include <boost\mpl/eval_if.hpp>
#include <boost\mpl/identity.hpp>
#include <boost\mpl/apply.hpp>
#include <boost\mpl/next.hpp>
#include <boost\mpl/not_equal_to.hpp>
#include <boost\mpl/greater.hpp>
#include <boost\mpl/minus.hpp>
#include <boost\mpl/plus.hpp>
#include <boost\mpl/multiplies.hpp>
#include <boost\mpl/int.hpp>
#include <boost\mpl/placeholders.hpp>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

namespace Exercise_4_3 {

	namespace Original_1 {

		template<typename N, typename Predicate>
		struct next_if : mpl::if_<
			typename mpl::apply<Predicate,N>::type
			,typename mpl::next<N>::type
			,N
		>
		{};

		template<typename V>
		struct v_is_positive : mpl::bool_ < (V::value > 0) >
		{};

		void call_next_if()
		{
			typedef next_if<_1, v_is_positive<_1>>::type	type_for_next_if;


		}

	}

	namespace Solution_1 {

	}
}

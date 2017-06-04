#include "stdafx.h"

#include "Exercises_4.hpp"

#include <boost/mpl/if.hpp>
#include <boost\mpl/eval_if.hpp>
#include <boost\mpl/identity.hpp>
#include <boost\mpl/apply.hpp>
#include <boost\mpl/next.hpp>
#include <boost\mpl/not_equal_to.hpp>
#include <boost\mpl/equal_to.hpp>
#include <boost\mpl/greater.hpp>
#include <boost\mpl/minus.hpp>
#include <boost\mpl/plus.hpp>
#include <boost\mpl/multiplies.hpp>
#include <boost\mpl/int.hpp>
#include <boost\mpl/placeholders.hpp>
#include <boost\mpl/assert.hpp>
#include <boost\mpl/is_sequence.hpp>
#include <boost\mpl/vector.hpp>
#include <boost\type_traits\is_same.hpp>


namespace mpl = boost::mpl;

using namespace boost::mpl::placeholders;

namespace Exercise_4_1 {

	template<typename T>
	struct FailsIfInstantiated
	{
		static_assert(boost::is_integral<T>::value, "T must be integral");
	};

	void doShortCircuit()
	{
		// how do I know an expression is not invoked? Use the above structure!!
		
#define MAKE_BOTH_ARGS_INSTANTIATE

		typedef mpl::or_ < mpl::true_, FailsIfInstantiated<double> >::type res;

#ifdef MAKE_BOTH_ARGS_INSTANTIATE
		typedef mpl::or_ < mpl::false_, FailsIfInstantiated<double> >::type res2;
#endif

		typedef mpl::and_< mpl::false_, FailsIfInstantiated<double>>::type res3;

#ifdef MAKE_BOTH_ARGS_INSTANTIATE
		typedef mpl::and_< mpl::true_, FailsIfInstantiated<double>>::type res4;
#endif
	}
}

namespace Exercise_4_3 {

	namespace Section_1 {
		template<typename V>
		struct v_is_positive : mpl::bool_ < (V::value > 0) >
		{};

		namespace Original {

			template<typename N, typename Predicate>
			struct next_if : mpl::if_<
				typename mpl::apply<Predicate, N>::type
				, typename mpl::next<N>::type
				, N
			>
			{};

			void call_next_if()
			{

				typedef next_if<mpl::int_<3>, v_is_positive<_1>>::type	next_if_3;

				auto val = next_if_3::value;
				std::cout << val << std::endl;

				typedef next_if<mpl::int_<-3>, v_is_positive<_1>>::type	next_if_minus_3;

				val = next_if_minus_3::value;
				std::cout << val << std::endl;

			}
		}

		namespace Remove_unnecessary_instantiations
		{
			template<typename N, typename Predicate>
			struct next_if : mpl::if_<
				typename mpl::apply<Predicate, N>::type
				, typename mpl::next<N>
				, N
			>::type
			{};
			// OR:
			template<typename N, typename Predicate>
			struct eval_next_if : mpl::eval_if<
				typename mpl::apply<Predicate, N>::type
				, typename mpl::next<N>
				, N
			>
			{};


			void call_next_if()
			{
				typedef next_if<mpl::int_<3>, v_is_positive<_1>>::type	next_if_3;

				auto val = next_if_3::value;
				std::cout << val << std::endl;

				typedef next_if<mpl::int_<-3>, v_is_positive<_1>>::type	next_if_minus_3;

				val = next_if_minus_3::value;
				std::cout << val << std::endl;

				typedef eval_next_if<mpl::int_<3>, v_is_positive<_1>>::type	eval_next_if_3;
				static_assert(eval_next_if_3::value == 4, "value must be 4");
				BOOST_MPL_ASSERT_RELATION(eval_next_if_3::value, == , 4);

			}
		}
	}
	namespace Section_2
	{
		namespace Original
		{
			template <typename N1, typename N2>
			struct formula
				// level 0
				: mpl::if_<
				// level 1
				mpl::not_equal_to<N1, N2>
				, typename mpl::if_<
				// level 2
				mpl::greater<N1, N2>
				, typename mpl::minus<N1, N2>::type
				, N1
				>::type
				// level 1
				, typename mpl::plus<
				// level 2
				N1
				, typename mpl::multiplies<N1
				, mpl::int_<2>
				>::type
				// level 1
				>::type
				// level 0
				>::type
			{};

			void doFormula()
			{
				typedef formula<mpl::int_<4>, mpl::int_<2>>::type res;
				static_assert(res::value == 2, "Result must be 2");

				typedef formula<mpl::int_<2>, mpl::int_<2>>::type res2;
				static_assert(res2::value == 6, "Result must be 6");

				typedef formula<mpl::int_<1>, mpl::int_<2>>::type res3;
				static_assert(res3::value == 1, "Result must be 1");

			}
		}
		namespace Remove_unnecessary_instantiations
		{
			template <typename N1, typename N2>
			struct formula
				: mpl::if_<
				mpl::not_equal_to<N1, N2>
				, typename mpl::if_<
				mpl::greater<N1, N2>
				, mpl::minus<N1, N2>
				, N1
				>
				, typename mpl::plus<
				N1
				, typename mpl::multiplies<N1
				, mpl::int_<2>
				>
				>
				>::type
			{};

			void doFormula()
			{
				typedef formula<mpl::int_<5>, mpl::int_<2>>::type res;
				static_assert(res::value == 3, "Result must be 3");

				typedef formula<mpl::int_<2>, mpl::int_<2>>::type res2;
				static_assert(res2::value == 6, "Result must be 6");

				typedef formula<mpl::int_<1>, mpl::int_<2>>::type res3;
				static_assert(res3::value == 1, "Result must be 1");
			}

		}
	}
}




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
#include <boost\type_traits.hpp>
#include <boost\mpl/or.hpp>
#include <boost\type_traits\is_member_object_pointer.hpp>


namespace mpl = boost::mpl;

using namespace boost::mpl::placeholders;

namespace Exercise_4_0 {

	template<typename T>
	struct FailsIfInstantiated
	{
		static_assert(boost::is_integral<T>::value, "T must be integral");
		constexpr static const bool value = boost::is_integral<T>::value;
		typedef FailsIfInstantiated type;
	};

	// type must have nested:
	// static const bool value
	// typedef XX type;

	namespace JD {

		struct accesses_static_var
		{
			static const int value = 99;
			constexpr int getValue()  { return value; }
		};
		template< bool C_ > struct bool_
		{
			static const bool value = C_;
			typedef mpl::integral_c_tag tag;
			typedef bool_ type;
			typedef bool value_type;
			constexpr operator bool() const { return this->value; }
		};

		void useJDbool_()
		{
			constexpr bool val = bool_<false>{};
			constexpr int v = accesses_static_var().getValue();
		}
	}

	void doShortCircuit()
	{
		// how do I know an expression is not invoked? Use the above structure!!
		
#define MAKE_BOTH_ARGS_INSTANTIATE

		typedef mpl::or_ < mpl::true_, FailsIfInstantiated<double> >::type res;
		constexpr bool same = boost::is_same<res, mpl::bool_<true>>::value;

#ifdef MAKE_BOTH_ARGS_INSTANTIATE
		typedef mpl::or_ < mpl::false_, FailsIfInstantiated<int> >::type res2;
#endif

		typedef mpl::and_< mpl::false_, FailsIfInstantiated<double>>::type res3;

#ifdef MAKE_BOTH_ARGS_INSTANTIATE
		//typedef mpl::and_< mpl::true_, FailsIfInstantiated<double>>::type res4;
#endif
	}
}

namespace Exercise_4_1 {

	template<typename N1, typename N2>
	struct logical_or  : mpl::bool_<
		mpl::eval_if<
			N1,
			mpl::true_,
		mpl::eval_if<
			N2,
			mpl::true_,
			mpl::false_>
		>::type::value
	>
	{};


	template<typename N1, typename N2>
	struct logical_and : mpl::bool_<
		mpl::eval_if<
		mpl::not_<N1>,
		mpl::false_,
		mpl::eval_if<
		mpl::not_<N2>,
		mpl::false_,
		mpl::true_>
		>::type::value
	>
	{};

	namespace Using_if_
	{
		template<typename N1, typename N2>
		struct logical_or : mpl::bool_<
			mpl::if_<
			N1,
			mpl::true_,
			mpl::if_<
			N2,
			mpl::true_,
			mpl::false_>
			>::type::type::value
		>
		{};

	}
	void doShortCircuit()
	{
		using Exercise_4_0::FailsIfInstantiated;

		// how do I know an expression is not invoked? Use the above structure!!

#define MAKE_BOTH_ARGS_INSTANTIATE

		typedef logical_or < mpl::true_, FailsIfInstantiated<double> >::type res;
		constexpr bool same = boost::is_same<res, mpl::bool_<true>>::value;

#ifdef MAKE_BOTH_ARGS_INSTANTIATE
		typedef logical_or < mpl::false_, FailsIfInstantiated<int> >::type res2;
		//typedef logical_or < mpl::false_, FailsIfInstantiated<double> >::type res_2;

#endif
		Using_if_::logical_or<mpl::false_, FailsIfInstantiated<int>>::type res_22;
		Using_if_::logical_or<mpl::true_, FailsIfInstantiated<double>>::type res_23;


		typedef logical_and< mpl::false_, FailsIfInstantiated<double>>::type res3;

#ifdef MAKE_BOTH_ARGS_INSTANTIATE
		//typedef logical_and< mpl::true_, FailsIfInstantiated<double>>::type res4;
#endif
	}
}

namespace Exercise_4_2 {

	template<typename N1, typename N2, typename N3=mpl::false_, typename N4=mpl::false_, typename N5=mpl::false_>
	struct logical_or : mpl::bool_<
		mpl::eval_if<
		N1,
		mpl::true_,
		mpl::eval_if<
		N2,
		mpl::true_,
		mpl::eval_if<
		N3,
		mpl::true_,
		mpl::eval_if<
		N4,
		mpl::true_,
		mpl::eval_if<
		N5,
		mpl::true_,
		mpl::false_>
		>
		>
		>
		>::type::value
	>
	{};

	template<typename N1, typename N2, typename N3 = mpl::true_, typename N4 = mpl::true_, typename N5 = mpl::true_>
	struct logical_and : mpl::bool_<
		mpl::eval_if<
		mpl::not_<N1>,
		mpl::false_,
		mpl::eval_if<
		mpl::not_<N2>,
		mpl::false_,
		mpl::eval_if<
		mpl::not_<N3>,
		mpl::false_,
		mpl::eval_if<
		mpl::not_<N4>,
		mpl::false_,
		mpl::eval_if<
		mpl::not_<N5>,
		mpl::false_,
		mpl::true_>
		>
		>
		>
		>::type::value
	>
	{};

	void doShortCircuit()
	{
		using Exercise_4_0::FailsIfInstantiated;

		// how do I know an expression is not invoked? Use the above structure!!

#define MAKE_BOTH_ARGS_INSTANTIATE

		typedef logical_or < mpl::true_, FailsIfInstantiated<double> >::type res;
		constexpr bool same = boost::is_same<res, mpl::bool_<true>>::value;

#ifdef MAKE_BOTH_ARGS_INSTANTIATE
		typedef logical_or < mpl::false_, FailsIfInstantiated<int> >::type res2;
		//typedef logical_or < mpl::false_, FailsIfInstantiated<double> >::type res_2;

#endif


		typedef logical_and< mpl::false_, FailsIfInstantiated<double>>::type res3;

#ifdef MAKE_BOTH_ARGS_INSTANTIATE
		//typedef logical_and< mpl::true_, FailsIfInstantiated<double>>::type res4;
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

namespace Integral_operators
{
	void doIntegralOperators()
	{
		typedef mpl::int_<4>::type	four;
		typedef mpl::next<four>::type five;
		typedef mpl::prior<four>::type three;

	}
}

namespace Exercise_4_4
{
	
	/// <summary>	is_data_member_pointer. </summary>
	struct A
	{
		std::string name;
		std::string last_name;
		void setName(const std::string& s)
		{
			name = s;
		}
	};


	template<typename T>
	struct is_function_member : mpl::false_
	{};

	template< typename DataType, typename StructType, typename ...Args>
	struct is_function_member<DataType (StructType::*)(Args...)> : mpl::true_
	{
		typedef DataType Ret;
	};

	template<typename T>
	struct is_data_member_pointer : mpl::bool_ <
		mpl::and_<boost::is_member_pointer<T>, mpl::not_< is_function_member<T>>>::value >
	{};

	void doFirst()
	{
		A a;
		using Pm = std::string A::*;
		using Pf = void (A::*)(const std::string&);
		Pm p = &A::name;
		Pf f = &A::setName;
		
		constexpr bool _is_function_m_Pf = is_function_member<Pf>::value;
		static_assert(_is_function_m_Pf == true);

		constexpr bool _is_function_m_Pm = is_function_member<Pm>::value;
		static_assert(_is_function_m_Pm == false);

		constexpr bool _is_data_pointer_Pm = is_data_member_pointer<Pm>::value;
		static_assert(_is_data_pointer_Pm == true);

		constexpr bool _is_data_pointer_Pf = is_data_member_pointer<Pf>::value;
		static_assert(_is_data_pointer_Pf == false);
	}
}


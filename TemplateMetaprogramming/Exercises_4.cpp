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
#include <vector>


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

	void aFunction()
	{
	}

	template<typename T>
	struct is_function_member : mpl::false_
	{};

	template< typename DataType, typename StructType, typename ...Args>
	struct is_function_member<DataType (StructType::*)(Args...)> : mpl::true_
	{
		typedef DataType Ret;
	};

	template<typename T>
	struct is_a_function : mpl::false_ {};

	template<typename RetType, typename ...Args>
	struct is_a_function<RetType (Args...)> : mpl::true_ {};
#if 0
	template<typename T>
	struct is_pointer_to_function : mpl::false_ {};

	template<typename RetType, typename ...Args>
	struct is_pointer_to_function<RetType (*)(Args...)> : mpl::true_ {};
#endif
#if 0
	template <typename T>
	struct is_pointer_to_function : mpl::bool_<
		mpl::and_< boost::is_pointer<T>, boost::is_function< boost::remove_pointer<T>>>::value
	>
	{};
#endif

	namespace helper
	{
		template<typename T>
		struct is_pointer_to_function_impl
		{
			constexpr static bool _is_pointer = boost::is_pointer<T>::value;
			typedef typename boost::remove_pointer<T>::type	T_pointer_removed;
			constexpr static bool _is_function = boost::is_function<T_pointer_removed>::value;
			constexpr static bool value = _is_pointer && _is_function;
		};
	}

	template <typename T>
	struct is_pointer_to_function :  mpl::bool_< helper::is_pointer_to_function_impl<T>::value >
	{};

	namespace alternative
	{
		template <typename T>
		struct is_pointer_to_function : mpl::bool_ <
			mpl::and_< boost::is_pointer<T>, boost::is_function<typename boost::remove_pointer<T>::type>>::value
		>
		{};


	}

	template<typename T>
	struct is_reference_to_function_pointer : mpl::bool_<
		is_pointer_to_function<boost::remove_reference<T>>::value
	>
	{};

	template<typename T>
	struct is_reference_to_non_const : mpl::bool_<
		mpl::and_<boost::is_reference<T>, mpl::not_< boost::is_const<typename boost::remove_reference<T>::type>>>::value
	>
	{};


	//int*&
//	template<typename RetType, typename ...Args>
//	struct is_reference_to_function_pointer<RetType (* const &)(Args...)> : mpl::true_ {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	The is data member pointer.
	/// 			First sub exercise in 4.4 </summary>
	///
	/// <remarks>	Juan Dent, 15/6/2017. </remarks>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

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

		using Pff = void(*)();
		Pff aPff = aFunction;
		
		// is_pointer_to_function:
		typedef boost::remove_pointer<Pff>::type should_be_function;
		constexpr bool _x = boost::is_function<should_be_function>::value;
		static_assert(_x == true);

		{
			constexpr bool _x = boost::is_pointer<Pff>::value;
			typedef boost::remove_pointer<Pff>::type	ff;
			constexpr bool _y = boost::is_function<ff>::value;
			static_assert(_y == true);
		}

		{
			const int& f = 5;
			int x = 45;
			int& r = x;

			constexpr bool _f = is_reference_to_non_const<decltype(f)>::value;
			static_assert(_f == false);
			constexpr bool _r = is_reference_to_non_const<decltype(r)>::value;
			static_assert(_r == true);
			constexpr bool _x = is_reference_to_non_const<decltype(x)>::value;
			static_assert(_x == false);
		}
		using Rf = void(*&)();
		//Rf rF = aFunction;

		// is_reference_to_function_pointer:
		typedef boost::remove_reference<Rf>::type should_be_function_pointer;
		constexpr bool _y = is_pointer_to_function<should_be_function_pointer>::value;
		static_assert(_y == true);


		constexpr bool _is_pointer_aPff = is_pointer_to_function<Pff>::value;
		static_assert(_is_pointer_aPff == true);

		constexpr bool _is_a_function_aFunction = is_pointer_to_function<decltype(aFunction)>::value;
		static_assert(_is_a_function_aFunction == false);

		using RPF = void(* const&)();
		RPF rPf = aFunction;

		constexpr bool _is_reference = boost::is_reference<decltype(rPf)>::value;
		static_assert(_is_reference == true);

		typedef boost::remove_reference<RPF>::type no_ref;
		typedef boost::remove_const<no_ref>::type no_const;

		constexpr bool _is_pointer_function = is_pointer_to_function< boost::remove_reference< decltype(rPf)>::type>::value;


		constexpr bool _is_reference_to_function_pointer = is_reference_to_function_pointer<decltype(rPf)>::value;

	}
}

namespace Exercise_4_5
{
	template <typename Container, typename Value>
	typename mpl::if_< boost::is_const<Container>, typename Container::const_iterator, typename Container::iterator>::type
		container_find(Container& c, Value const& v)
	{
		return std::find(c.begin(), c.end(), v);
	}

	void searchVector()
	{
		std::vector<int> v{ 1,2,3,4,5,6 };
		constexpr bool _v_const = boost::is_const<decltype(v)>::value;
		static_assert(_v_const == false);

		auto at = container_find(v, 4);

		const std::vector<int> cv{ v };
		constexpr bool _cv_const = boost::is_const<decltype(cv)>::value;
		static_assert(_cv_const == true);

		auto cat = container_find(cv, 4);

		typedef mpl::if_< boost::is_const<decltype(v)>, typename decltype(v)::const_iterator, typename decltype(v)::iterator>::type ret;
	}
}
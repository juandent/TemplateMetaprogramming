//
//  exercise_3_1.cpp
//  TemplateMetaprogramming
//
//  Created by Juan Dent on 29/August/16.
//  Copyright © 2016 Juan Dent. All rights reserved.
//

#include "stdafx.h"

#include "exercise_3_1.hpp"
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
#include <ratio>


// Dimensions (pg 40 -- C++ Template Metaprogramming
namespace mpl = boost::mpl;
using namespace mpl::placeholders;
using namespace std;

// binary lambda expression applied to 2 additional arguments:
BOOST_STATIC_ASSERT((mpl::plus<
                     mpl::int_<2>
                     , mpl::int_<3>
                     >::type::value == 5
                     ));


namespace Chapter3 {
	namespace mpl = boost::mpl;

	namespace QuantityStuff {
		typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
		typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
		typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
		typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
		typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
		typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
		typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> amount_of_substance;

		//                        m l  t
		typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;         // l/t
		typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;     // l/(t2)
		typedef mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;         // ml/t
		typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;            // ml/(t2)

		template<typename T, typename Dimensions>
		struct quantity
		{
			explicit quantity(T x) : m_value{ x } {}

			template<typename OtherDimensions>
			quantity(quantity<T, OtherDimensions> const& rhs) : m_value{ rhs.value() }
			{
				BOOST_STATIC_ASSERT((mpl::equal<Dimensions, OtherDimensions>::type::value));
			}

			T value() const { return m_value; }
		private:
			T m_value;
		};

		// implement addition and subtraction
#ifdef SAME_DIMENSION_FOR_ARGUMENTS
		template<typename T, typename D>
		quantity<T, D>
			operator+(quantity<T, D> x, quantity<T, D> y)
		{
			return quantity<T, D>{ x.value() + y.value() };
		}
#else
	// SOLUTION for Exercise 3.5:
		template<typename T, typename D, typename OtherDimensions>
		quantity<T, D>
			operator+(quantity<T, D> x, quantity<T, OtherDimensions> y)
		{
			BOOST_STATIC_ASSERT((mpl::equal<D, OtherDimensions>::type::value));
			return quantity<T, D>{ x.value() + y.value() };
		}
#endif

		template<typename T, typename D>
		quantity<T, D>
			operator-(quantity<T, D> x, quantity<T, D> y)
		{
			return quantity<T, D>{ x.value() - y.value() };
		}
		// create metafunction class for plus
		struct plus_f
		{
			template<typename T1, typename T2>
			struct apply
			{
				typedef typename mpl::plus<T1, T2>::type type;
			};
		};
		// implementing multiplication
		template<typename T, typename D1, typename D2>
		quantity<
			T
			, typename mpl::transform<D1, D2, plus_f>::type
		>
			operator*(quantity<T, D1> x, quantity<T, D2> y)
		{
			typedef typename mpl::transform<D1, D2, plus_f>::type dim;
			return quantity<T, dim>(x.value() * y.value());
		}

#ifdef DIRECT_DIVISION_IMPLEMENTATION    
		// implementing division
		template<typename T, typename D1, typename D2>
		quantity<
			T
			, typename mpl::transform<D1, D2, mpl::minus<_1, _2>>::type
		>
			operator/ (quantity<T, D1> x, quantity<T, D2> y)
		{
			typedef typename mpl::transform<D1, D2, mpl::minus<_1, _2>>::type dim;

			return quantity<T, dim>(x.value() / y.value());
		}
#endif

		// metafunction for getting divide_dimensions (via forwarding)
		template<typename D1, typename D2>
		struct divide_dimensions : mpl::transform<D1, D2, mpl::minus<_1, _2>>
		{};

		// alternate division implementation:
		template<typename T, typename D1, typename D2>
		quantity<
			T
			, typename divide_dimensions<D1, D2>::type
		>
			operator/ (quantity<T, D1> x, quantity<T, D2> y)
		{
			return quantity<T, typename divide_dimensions<D1, D2>::type>(x.value() / y.value());
		}

		/* &useQuantities& */
		void useQuantities()
		{
			quantity<float, length> l{ 1.0f };
			quantity<float, mass> m{ 2.0f };
			quantity<float, length> l2{ 4.0f };
			quantity<float, acceleration> a{ 2.0f };


			std::cout << "force: " << (m*a).value() << std::endl;

			//quantity<float, mass> mm = m*a; // should fail!!
			quantity<float, force> f = m*a;

			auto acc = f / m;

			f = f + m*a;

			std::cout << "force: " << f.value() << std::endl;

			auto r = l + l2;
			r = l - l2;
			//auto yy = l+m;
		}
	}

	namespace Questions
	{
		namespace Q3_0
		{
			template< unsigned long N>
			struct binary
			{
				static unsigned long constexpr value = binary<N / 10>::value * 2 + N % 10;
				static_assert(N % 10 < 2, "invalid digit - not 0 nor 1");
			};

			template<>
			struct binary<0>
			{
				static unsigned long constexpr value = 0;
			};

			void useBinary()
			{
				unsigned long constexpr one = binary<1>::value;
				unsigned long constexpr three = binary<11>::value;
				unsigned long constexpr four = binary<100>::value;
			}
		}
		namespace Q3_1
		{
			typedef ::mpl::vector3_c<int, 1, 2, 3> sequence;

			void useTransform()
			{
				typedef typename mpl::transform < mpl::vector_c<int, 1, 2, 3>, mpl::times<_1, mpl::int_<2>>>::type result;
				result t;
			}
		}
		namespace Q3_8
		{
			// units for length
			namespace Length
			{
				typedef ratio<1, 1>			mm;
				typedef ratio<10, 1>		cm;
				typedef ratio<1000, 1>		m;
				typedef ratio<1'000'000, 1>	km;
				typedef ratio<254, 10>		in;

				template< class TargetUnits, class SourceUnits>
				struct factor
				{
				private:
					typedef  ratio_divide<TargetUnits, SourceUnits> r;
				public:
					static constexpr long double convertToSmaller(long double source)
					{
						return convert_helper< ( r::num >= r::den) >::convert(source);
					}

				private:
					template<bool>
					struct convert_helper
					{
						static constexpr long double convert(long double source)
						{
							return (source * r::den) / r::num;
						}
					};
					template<> struct convert_helper<false>
					{
						static constexpr long double convert(long double source)
						{
							return (source * r::num) / r::den;
						}
					};
				};
				
#if 0
				template < class TargetUnits, class SourceUnits>
				struct factor
				{
				private:
					typedef  ratio_divide<TargetUnits, SourceUnits> r;
				public:
#if 0
					//template<typename = enable_if<r::num >= r::den>::type >
					static long double convertToSmallerUnit(long double source)
					{
						source *= r::den;
						source /= r::num;
						return source;
					}
					//template<typename = enable_if<r::num < r::den>::type >
						static long double convertToSmallerUnit(long double source)
						{
							source *= r::num;
							source /= r::den;
							return source;
						}
#endif
					static long double convert(long double source)
					{
						source *= r::den;
						source /= r::num;
						return source;
					}
#if 1
					static long double convertToSmaller(long double source)
					{
						if (r::num >= r::den)
						{
							source *= r::den;
							source /= r::num;
							return source;
						}
						else
						{
							source *= r::num;
							source /= r::den;
							return source;
						}
					}
#endif
				};
#endif

				namespace using_int_
				{

					// template parameters must be integral wrappers with the value member exposed!
					// this can be mpl::int_<N>, as a possible implementation
					template <class U1, class U2>
					struct factor
					{
					private:
						static constexpr bool U1Smaller = std::conditional < U1::value < U2::value, std::true_type, std::false_type>::type::value;
					public:
						typedef typename std::conditional < U1Smaller, U1, U2>::type smaller_type;
						typedef typename std::conditional < !U1Smaller, U1, U2>::type larger_type;
						typedef smaller_type type;
						typedef typename mpl::divides< larger_type, smaller_type>::type division_type;
						static constexpr unsigned long long value = division_type::value;

					};
				}

				void useLength()
				{
					typedef  ratio_divide<cm, mm> r;

					auto valinum = 15.0;
					valinum *= r::den;
					valinum /= r::num;
					cout << valinum << endl;

					//cout << factor<cm, mm>::convert(15) << endl;

					cout << factor<in, cm>::convertToSmaller(25.4) << endl;
#if 0
					using ff = factor<cm, mm>;
					cout << ff::value << endl;
					ff::smaller_type small;
					ff::larger_type large;
					ff::division_type div;
					std::cout << ff::division_type::value << std::endl;
					ff value;
					auto val = ff::value;
					using fff = factor<mm, cm>::division_type;
					auto other = fff::value;
#endif
				}
			}
			template <class T, class Dimensions, class Unit>
			struct quantity
			{
				template< class OtherUnit>
				explicit quantity(T x)
				{
					using f = Length::factor<Unit, OtherUnit>;
					auto constexpr fac = f::value;

				}
				T value() const { return m_value;  }
			private:
				T m_value;
			};
		}
	}
	namespace HigherOrderMetafunctions
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	calling meta function class with metafn forwarding. </summary>
		///
		/// <remarks>	Juan Dent, 11/2/2017. </remarks>
		///
		/// <typeparam name="UnaryMetaFunctionClass"> Type of the unary meta function class. </typeparam>
		/// <typeparam name="Arg">					  Type of the argument. </typeparam>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		template <typename UnaryMetaFunctionClass, typename Arg>
		struct apply1 : UnaryMetaFunctionClass::template apply<Arg>
		{};

		// now twice (f(f(x))  -- where f is a metafunction class -- is:
		template <typename F, typename X>
		struct twice : apply1<F, typename apply1<F,X>::type>
		{};

		// now thrice (f(f(x))) -- where f is a metafunction class:
		template <typename F, typename X>
		struct thrice : apply1<F, typename apply1<F, typename apply1<F,X>::type>::type>
		{};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	"Call" metafunction twice with F as std::add_pointer<_1> and X as type double. </summary>
		///
		/// <remarks>	Will not work because std::add_pointer<_1> is not a metafn class!!
		/// 			Juan Dent, 11/2/2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		// this does  not work because std::add_pointer<_1> is not a metafn class and has no nested template<...> apply type
		// 
		typedef twice< std::add_pointer<_1>, double> twice_pointer_double_not_ok;

		// create metafunction class for add_pointer<T>
		struct add_pointer_f
		{
			template <typename T>
			struct apply : std::add_pointer<T>
			{};
		};
		typedef typename twice< add_pointer_f, double>::type twice_pointer_double;
		typedef typename thrice< add_pointer_f, double>::type thrice_pointer_double;

		namespace OurLambda
		{
#if 0
			// a placeholder is defined like so:
			template <int X>
			struct PlaceHolder;

			template<>
			struct PlaceHolder<1>
			{
				typedef PlaceHolder<1> type;

				template<typename C1, typename C2=void, typename C3=void>
				struct apply
				{
					typedef C1 type;
				};
			};
			typedef PlaceHolder<1> _1;

			template<>
			struct PlaceHolder<2>
			{
				typedef PlaceHolder<2> type;

				template<typename C1, typename C2, typename C3 = void>
				struct apply
				{
					typedef C2 type;
				};
			};
			typedef PlaceHolder<2> _2;

			template<>
			struct PlaceHolder<3>
			{
				typedef PlaceHolder<3> type;

				template<typename C1, typename C2, typename C3>
				struct apply
				{
					typedef C3 type;
				};
			};
			typedef PlaceHolder<3> _3;
#endif

			 
			namespace Debug
			{
				template<typename T>
				struct TypeDecl;
			}


			// In the general case, F is either a metafunction class or a placeholder expression
			// We will deal with placeholder expressions in partially specialized templates of this one
			// In this particular case, we assume F is a metafunction class (i.e. it contains a nested 
			// metafunction called apply - a metafunction is a template or class if it does not have 
			// non-type parameters and if it also returns a type called type -- i.e. nested) 
			template <typename F>
			struct lambda
			{
				typedef F type;

				//typedef lambda type;
				
				//Debug::TypeDecl<F> lambda_f_instantiated;

				template< typename... Args>
				struct apply
				{
					typedef typename F::template apply<Args...>::type type;
					//typedef typename F<Args...>::type type;
				};


			};

			template<template<typename> class F>
			struct lambda<F<_1>>		// matches add_pointer<_1>
			{
				typedef lambda<F<_1>> type;

				//Debug::TypeDecl<_1> lambda_f_1_instantiated;

				template<typename... Args>
				struct apply
				{
					typedef typename F<Args...>::type type;		// invokes add_pointer<Arg>
				};
			};


			template<template<typename, typename> class F>
			struct lambda<F<_1,_2>>		// matches mpl::plus<_1,_2>
			{
				typedef lambda<F<_1,_2>> type;

				//Debug::TypeDecl<_1> lambda_f_1_2_instantiated;

				template<typename... Args>
				struct apply
				{
					//TypeDecl<Arg0> a_variable_forArg0;
					typedef typename F<Args...>::type type;		// invokes mpl::plus<Arg0, Arg1>
				};
			};


			template <typename F, typename... Args>
			struct apply : lambda<F>::type::template apply<Args...>
			{
				//Debug::TypeDecl<typename lambda<F>::type> apply_instantiated;
			};

#if 0
			template <template <typename> class F, typename... Args>
			struct apply<F<_1>, Args...> : lambda<F<_1>>::type::template apply<Args...>
			{
				//TypeDecl<F<_1>> a_variable;
			};


			template <template <typename, typename> class F, typename... Args>
			struct apply<F<_1,_2>, Args...> : lambda<F<_1,_2>>::template apply<Args...>
			{};
#endif

			// create metafunction class for add_pointer<T>
			struct add_pointer_f
			{
				template <typename T>
				struct apply : std::add_pointer<T>
				{};
			};
			// create metafunction class for mpl::plus<T1,T2>
			struct plus_f
			{
				template <typename T1, typename T2>
				struct apply : mpl::plus<T1,T2>
				{};
			};

			struct common_f
			{
				template <typename T1, typename T2>
				struct apply : std::common_type<T1,T2>
				{
					typedef typename std::common_type<T1, T2>::type type;
				};
			};

			template<typename T1, typename T2>
			struct common_type_metafunction : std::common_type<T1,T2>
			{};

			template<size_t N>
			struct integral
			{
				static constexpr size_t value = N;
			};

			void useOurLambda()
			{
				// work on add_pointer<_1>
				
				typedef typename apply<add_pointer_f, long>::type long_one_pointer;
				long_one_pointer p = nullptr;

				typedef typename apply<std::add_pointer<_1>, long>::type another_long_one_pointer;
				another_long_one_pointer pp = nullptr;

				auto val = apply<plus_f, mpl::int_<3>, mpl::int_<9>>::type::value;

				typedef typename apply<common_f, float, long>::type common;
				common cc;

				// this did not work because std::plus is a functor not a metafunction!!
				// 
				//typedef typename apply< mpl::plus<_1,_2>, mpl::int_<3>, mpl::int_<7>>::type twelve;
				
				typedef typename apply<common_type_metafunction<_1,_2>, float, long>::type common_type;
				common_type ccc;
				//common_type_metafunction<_1, _2>::type ss;
				//Debug::TypeDecl<decltype(ss)> ss_name;

				//typedef typename apply<std::common_type<_1, _2>, float, long>::type other_common_type;
				//other_common_type occ;
			}
		}

		namespace LambdaExpressions
		{
			// create twice to work with either metafn classes or placeholder expressions (i.e. any lambda expression)
			template <typename F, typename Arg>
			struct twice : apply1< typename mpl::lambda<F>::type,
				typename apply1< typename mpl::lambda<F>::type, Arg>::type>
			{};

			typedef typename twice< std::add_pointer<_1>, int>::type twice_pointer_int;

			// works with either metafn classes or placeholder expressions (i.e. any lambda expression)
			template <typename F, typename Arg>
			struct apply : mpl::lambda<F>::type::template apply<Arg>
			{};

			// now generalize apply to use variadic templates
			namespace Variadic
			{
				template<typename F, typename...Args>
				struct apply : mpl::lambda<F>::type::template apply<Args...>
				{};
			}

			template <typename T>
			using plus_five = mpl::plus<T, mpl::int_<5>>;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Use twice pointer double. </summary>
		///
		/// <remarks>	Juan Dent, 11/2/2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void useTwicePointerDouble()
		{
			twice_pointer_double d;
			apply1<add_pointer_f, double>::type f;
			std::cout << std::is_same<double*, apply1<add_pointer_f, double>::type>::value << std::endl;
			std::cout << std::is_same<double**, twice_pointer_double>::value << std::endl;
			std::cout << std::is_same<double***, thrice_pointer_double>::value << std::endl;
			LambdaExpressions::twice_pointer_int i;
			std::cout << std::is_same<int**, LambdaExpressions::twice_pointer_int>::value << std::endl;

			std::cout << std::is_same<double*, LambdaExpressions::apply<std::add_pointer<_1>, double>::type>::value << std::endl;

			LambdaExpressions::apply<std::vector<_1>, int>::type xx;
			xx.push_back(8);

			auto val = LambdaExpressions::Variadic::apply<mpl::plus<_1, _2>, mpl::int_<3>, mpl::int_<7>>::type::value;
			// partial metafn application:
			std::cout << LambdaExpressions::Variadic::apply<LambdaExpressions::plus_five<_1>, mpl::int_<2>>::type::value << std::endl;
			
			OurLambda::useOurLambda();
		}
	}
}

// C++ Template Metaprogramming
namespace Solution_to_Exercise_3_1 // 
{
    //#include <boost/mpl/vector_c.hpp>
    //#include <boost/mpl/transform.hpp>
    //#include <boost/mpl/placeholders.hpp>
    
    namespace mpl = boost::mpl;
    using namespace mpl::placeholders;
    
/* &solve& */
    void solve()
    {
        namespace mpl = boost::mpl;
        typedef mpl::vector_c<int,1,2,3> source_seq;
        typedef mpl::vector_c<int,1,1,1> next_seq;
        
        typedef typename mpl::transform<source_seq, next_seq, mpl::plus<_1,_2>>::type seq_for_exercise_3_1_sol_1;
        
        typedef typename mpl::transform<source_seq, source_seq, mpl::plus<_1,mpl::int_<1>>>::type seq_for_exercise_3_1_sol_2;
        
        std::cout << std::is_same<seq_for_exercise_3_1_sol_1, seq_for_exercise_3_1_sol_2>::value << std::endl;
        
        static_assert(std::is_same<seq_for_exercise_3_1_sol_1, seq_for_exercise_3_1_sol_2>::value, "");
        
        //typedef mpl::reverse_copy<seq_for_exercise_3_1_sol_1>::type exer_3_1_inverted;
        
        std::cout << mpl::at<seq_for_exercise_3_1_sol_1, mpl::int_<0>>::type::value << std::endl;
        std::cout << mpl::at<seq_for_exercise_3_1_sol_1, mpl::int_<1>>::type::value << std::endl;
        std::cout << mpl::at<seq_for_exercise_3_1_sol_1, mpl::int_<2>>::type::value << std::endl;
    }
}

namespace Solution_to_Exercise_3_2
{
    //#include <boost/mpl/vector_c.hpp>
    //#include <boost/mpl/transform.hpp>
    //#include <boost/mpl/placeholders.hpp>
    
    namespace mpl = boost::mpl;
    using namespace mpl::placeholders;
    
/* &solve& */
    void solve()
    {
        namespace mpl = boost::mpl;
        typedef mpl::vector_c<int,1,2,3> source_seq;
        
        typedef typename mpl::transform<source_seq, source_seq, mpl::times<_1,_2>>::type seq_for_exercise_3_2_sol_1;
        
        typedef typename mpl::transform<source_seq, source_seq, mpl::times<_1,_1>>::type seq_for_exercise_3_2_sol_2;
        
        std::cout << std::is_same<seq_for_exercise_3_2_sol_1, seq_for_exercise_3_2_sol_2>::value << std::endl;
        
        static_assert(std::is_same<seq_for_exercise_3_2_sol_1, seq_for_exercise_3_2_sol_2>::value,"");
        
        //typedef mpl::reverse_copy<seq_for_exercise_3_1_sol_1>::type exer_3_1_inverted;
        
        std::cout << mpl::at<seq_for_exercise_3_2_sol_1, mpl::int_<0>>::type::value << std::endl;
        std::cout << mpl::at<seq_for_exercise_3_2_sol_1, mpl::int_<1>>::type::value << std::endl;
        std::cout << mpl::at<seq_for_exercise_3_2_sol_1, mpl::int_<2>>::type::value << std::endl;
    }
}
    
namespace Solution_to_Exercise_3_3_AND_3_4
{
    // metafunction class for add_pointer
    struct add_pointer_f
    {
        template<class T>
        struct apply : boost::add_pointer<T> {};
    };
    
    
    template<class UnaryMetaFunctionClass, class Arg>
    struct apply1
    : UnaryMetaFunctionClass::template apply<Arg>
    {};
    
    template<class F, class X>
    struct twice 
    : apply1<F, typename apply1<F,X>::type>
    {};
    
    template<class X>
    struct two_pointers
    : twice<  typename mpl::lambda<boost::add_pointer<_1>>::type, X>
    {};
    
    // move lambda calling to twice_l struct
    template<class F, class X>
    struct twice_l
    : apply1<typename mpl::lambda<F>::type, 
            typename apply1<
                        typename mpl::lambda<F>::type
                        , X
                        >::type
            >
    {};
    
    template<class X>
    struct two_pointers_l : twice_l<boost::add_pointer<_1>, X>
    {};
    
    // SOLUTION TO 3.3:
    template<class X>
    struct four_pointers
    {
        typedef typename twice_l<boost::add_pointer<_1>, X>::type once; // f(x)
        typedef typename twice_l< boost::add_pointer<_1>, once >::type type;                   // f(f(x))
    };
    
    
    template<class F, class X>  // the BEST twice!
    struct twice_flexible
    :   mpl::apply<F, typename mpl::apply<F,X>::type>
    {};
    
    // SOLUTION TO 3.4 -- version 1
    template<class X>
    struct four_pointers_on_itself 
    {
        typedef typename twice_l< boost::add_pointer<_1>,   typename twice_l<boost::add_pointer<_1>, X>::type>::type type;
    };
    
    // SOLUTION TO 3.4 -- version 2
    template<class X>
    struct four_pointers_on_itself_inherit : twice_l< boost::add_pointer<_1>,   typename twice_l<boost::add_pointer<_1>, X>::type>
    {};
    
    // SOLUTION TO 3.4 -- version 3
    template<class X>
    struct four_pointers_on_itself_no_lambda 
    :  two_pointers<typename two_pointers<X>::type> 
    {};
    
    // SOLUTION TO 3.4 -- version 4
    template<class X>
    struct four_pointers_on_itself_inherit_no_lambda : twice< typename mpl::lambda<boost::add_pointer<_1>>::type,  typename twice<typename mpl::lambda< boost::add_pointer<_1>>::type, X>::type>
    {};
    
    // SOLUTION TO 3.4 -- version 5
    template<class X>
    struct four_pointers_via_twice_flexible : twice_flexible<boost::add_pointer<_1>, typename twice_flexible<boost::add_pointer<_1>, X>::type>
    {};
    
/* &use_add_pointer& */
    void use_add_pointer()
    {
        typedef two_pointers<int>::type TwoPointers;
        
        static_assert( boost::is_same<TwoPointers, int**>::value,"");
        
        static_assert( boost::is_same<four_pointers<int>::once, int**>::value,"");
        static_assert( boost::is_same<four_pointers<int>::type, int****>::value,"");
        
        static_assert( boost::is_same<four_pointers_on_itself<int>::type, int****>::value,"");
        
        int m = 0;
        int* pm = &m;
        int** ppm = &pm;
        int*** pppm = &ppm;
        four_pointers_on_itself<int>::type x = &pppm;
        
        four_pointers_on_itself_inherit<int>::type y = &pppm;
        
        four_pointers_on_itself_no_lambda<int>::type z = &pppm;
        
        four_pointers_on_itself_inherit_no_lambda<int>::type zz = &pppm;
        
        four_pointers_via_twice_flexible<int>::type zzz = &pppm;
    }
}


namespace Solution_to_Exercise_3_6
{
    template<class F, class X>  // the BEST twice!
    struct twice_flexible
    :   mpl::apply<F, typename mpl::apply<F,X>::type>
    {};

/* &solve& */
    void solve()
    {
        typedef typename mpl::apply<_1, typename mpl::apply<_1,_2>::type>::type twice_lambda_expression;
        
//        typedef twice_lambda_expression::apply<boost::add_pointer<_1>, int>::type the_lambda;
        
//        static_assert( std::is_same<the_lambda::type, int**>::value);
            
    }
}

namespace Solution_to_Exercise_3_7
{
/* &solve_3_7& */
    void solve_3_7()
    {
        using namespace std;
        
        // since _1 is a placeholder expression, then a metafunction class is generated, meaning that a metafunction apply<T> is available under the type generated
        // the second lambda invocation does nothing since it receives a metafunction class already...
        typedef mpl::lambda<mpl::lambda<_1>>::type t1;                      // IS A METAFUNCTION CLASS ==> has apply
    
        t1::apply<double>::type x1;
        
        static_assert( std::is_same<decltype(x1), double>::value,"");
        
        typedef mpl::lambda<_1>::type t0;
        
        t0::apply<double>::type x0;
        
        static_assert( std::is_same<decltype(x1), decltype(x0)>::value,"");
        
        t1 d;
        
        typedef mpl::apply<_1, mpl::plus<_1,_2>>::type t2;                  // NO ALTERNATE
        typedef mpl::apply<_1, std::vector<int>>::type t3;                  // NO ALTERNATE
        typedef mpl::apply<_1, std::vector<_1>>::type t4;                   // NO ALTERNATE
        typedef mpl::apply<mpl::lambda<_1>, std::vector<int>>::type t5;     // HAS NO APPLY
        typedef mpl::apply<mpl::lambda<_1>, std::vector<_1>>::type t6;      // HAS APPLY
        typedef mpl::apply<mpl::lambda<_1>, mpl::plus<_1,_2>>::type t7;     // HAS APPLY
        typedef mpl::apply<_1, mpl::lambda<mpl::plus<_1,_2>>>::type t8;     // HAS NO APPLY
        
        // for t2:
        auto val_t2 = 
        mpl::apply<
            t2
            ,mpl::int_<3>
        ,mpl::int_<5>
        >::type::value;
        cout << val_t2 << endl;
        
        // This next is true because std::vector<int> is not a metafunction template! (see pg 56)
        static_assert(std::is_same<t3, std::vector<int>>::value,"");
        // for t3:
        t3 val_t3 = {2,8};
        
        cout << val_t3[0] << endl;
        
        // for t4:
        typedef 
        mpl::apply<
            t4
        ,   double
        >::type t4_vec;
        t4_vec t4_vector = {3.5, 5.7};
        
        cout << t4_vector[0] << endl;
        
        // for t5:
        t5 val_t5 = {2,77,90};
        cout << val_t5[2] << endl;
        
        // This next is true because std::vector<int> is not a metafunction template! (see pg 56)
        static_assert(std::is_same<t5, std::vector<int>>::value,"");
        
        // alternate for t5: has no apply
        
        
        // for t6:
        typedef t6::apply<long long>::type t6_type;
        t6_type t6_obj = {100'000, 235'000};
        
        // alternate for t6:
        typedef mpl::apply<
            t6,
        long long>::type other_t6_type;
        other_t6_type t6_other_obj {300'000, 670'000};
        
        // t7:
        auto val_t7 = 
        mpl::apply<
            t7
        ,   mpl::int_<3>
        ,   mpl::int_<5>
        >::type::value;
        cout << val_t7 << endl;

        // alternative t7:
        cout << t7::apply< mpl::int_<60>, mpl::int_<20>>::type::value << endl;
    
        // for t8:
        auto val_t8 = 
        mpl::apply<
        t8
        ,mpl::int_<13>
        ,mpl::int_<50>
        >::type::value;
        cout << val_t8 << endl;

        // NO alternate for t8:
        
    }  
    
}


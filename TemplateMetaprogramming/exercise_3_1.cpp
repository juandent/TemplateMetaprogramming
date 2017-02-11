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


// Dimensions (pg 40 -- C++ Template Metaprogramming
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

// binary lambda expression applied to 2 additional arguments:
BOOST_STATIC_ASSERT((mpl::plus<
                     mpl::int_<2>
                     , mpl::int_<3>
                     >::type::value == 5
                     ));


namespace Chapter3 {
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

	namespace HigherOrderMetafunctions
	{
		// calling meta function class with metafn forwarding
		template <typename UnaryMetaFunctionClass, typename Arg>
		struct apply1 : UnaryMetaFunctionClass::template apply<Arg>
		{};

		// now twice (f(f(x))  -- where f is a metafunction class -- is:
		template <typename F, typename X>
		struct twice : apply1<F, typename apply1<F,X>::type>
		{};

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


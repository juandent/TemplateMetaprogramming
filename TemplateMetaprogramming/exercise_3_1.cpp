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
#include <boost/mpl/range_c.hpp>
#include <ratio>
#include <boost\mpl\vector.hpp>
#include <boost\mpl/size.hpp>

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
	namespace mpl = ::boost::mpl;

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
			namespace AddingUnitsToQuantity
			{
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

				// value for mixed dimensions (general case)
				//typedef mpl::vector_c<int, 

				// value for only one dimension (particular case)
				
				// units for length:
				typedef ratio<1, 1>			mm;
				typedef ratio<10, 1>		cm;		// how many mm in a cm: 10:1
				typedef ratio<1000, 1>		m;		// how many mm in a m:  1000:1
				typedef ratio<1'000'000, 1>	km;
				typedef ratio<254, 10>		in;		// how many mm in an inch: 254:10			(how many cm in an inch: 2.54)  

				// units for mass:
				typedef ratio<1, 1>			mg;
				typedef ratio<1000, 1>		g;		// how many mg in a g: 1000:1
				typedef ratio<1'000'000, 1>	kg;		// how many mg in a kg: 1'000'000:1

				// units for time
				typedef ratio<1, 1>			msec;
				typedef ratio<10, 1>		csec;	// how many msec in a csec: 10:1
				typedef ratio<1000, 1>		sec;	// how many msec in a sec: 1000:1

				// let's assume we only have 2 dimensions: length and mass
				//typedef mpl::vector_c<int, num_mass, den_mass, num_length, den_length>	units;

				// we start with dimensions given in base units, e.g.:
				typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;         // l/t
				// the base unit for distance is mm
				// the base unit for time is msec
				
				// say we have a velocity of 10.0 mm/msec
				// and we need that velocity to be given in m/sec
				
				// 1000 mm = 1 m
				// 1000 msec = 1 sec
				
				//10.0 mm/msec * 1/1000 = 0.01 m/msec
				//0.01 m/msec * 1000/1 = 10.0 m/sec

				// base units to m/sec
				typedef mpl::vector_c<int, 0, 1, 1000, 0, 0, 0, 0> numerators;
				typedef mpl::vector_c<int, 0, 1000, 1, 0, 0, 0, 0> denominators;

				template<typename BaseUnit, typename TargetUnit>
				struct ConversionFactor
				{
					typedef ratio_divide<BaseUnit, TargetUnit>	type;
					static unsigned long long constexpr numerator = type::num;
					static unsigned long long constexpr denominator = type::den;
				};



				// numerators:
				// typedef mpl::vector_c<int, 1000, 
				
				//typedef mpl::transform<units,
				// integer sequence
				 

				template< class TargetUnits, class SourceUnits>
				struct factor
				{
				private:
					typedef  ratio_divide<TargetUnits, SourceUnits> r;
				public:
					static constexpr long double convertToTarget(long double source)
					{
						return convert_helper< (r::num >= r::den) >::convert(source);
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
					template<> struct convert_helper<true>
					{
						static constexpr long double convert(long double source)
						{
							return (source * r::num) / r::den;
						}
					};
				};

				namespace OtherImplementationsForFactor
				{
					template < class TargetUnits, class SourceUnits>
					struct factor_using_enable_if
					{
					private:
						typedef  ratio_divide<TargetUnits, SourceUnits> r;
					public:
						static constexpr long double convertToSmaller(long double source)
						{
							return convert_helper(source, r{});
						}
					private:
						template< typename R>
						static constexpr
							typename enable_if< (R::num >= R::den), long double>::type
							convert_helper(long double source, R r)
						{
							return (source * R::den) / R::num;
						}
						template< typename R>
						static constexpr
							typename enable_if< (R::num < R::den), long double>::type
							convert_helper(long double source, R r)
						{
							return (source * R::num) / R::den;
						}

					};

					template < class TargetUnits, class SourceUnits>
					struct factor_using_tag_dispatch
					{
					private:
						typedef  ratio_divide<TargetUnits, SourceUnits> r;
					public:
						static constexpr long double convertToSmaller(long double source)
						{
							return convert_helper(source, integral_constant<bool, (r::num >= r::den)>{});
						}
					private:
						static constexpr long double convert_helper(long double source, true_type)
						{
							return (source * r::den) / r::num;
						}
						static constexpr long double convert_helper(long double source, false_type)
						{
							return (source * r::num) / r::den;
						}
					};

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
				}

				template <class T, class Dimensions, class Unit>
				struct quantity
				{
					template<class T, class OtherD, class OtherUnit>
					friend	struct quantity;

					explicit quantity(T x)
					{
						m_value = x;
					}
					T value() const { return m_value; }

					template<class T, class OtherD, class OtherUnit>
					quantity& operator+= (quantity<T, OtherD, OtherUnit> rhs)
					{
						using f = factor<Unit, OtherUnit>;	// Unit == target unit
						auto rhs_factored = f::convertToTarget(rhs.m_value);
						m_value += rhs_factored;
						return *this;
					}
				private:
					T m_value;
				};

				template<typename T, typename D, typename Unit, typename OtherD, typename OtherUnit>
				quantity<T, D, Unit>
					operator+(quantity<T, D, Unit> x, quantity<T, OtherD, OtherUnit> y)
				{
					BOOST_STATIC_ASSERT((mpl::equal<D, OtherD>::type::value));
					using f = factor<Unit, OtherUnit>;

					return quantity<T, D, Unit>{ x.value() + f::convertToTarget(y.value()) };
				}
				template<typename T, typename D, typename Unit, typename OtherD, typename OtherUnit>
				quantity<T, D, Unit>
					operator-(quantity<T, D, Unit> x, quantity<T, OtherD, OtherUnit> y)
				{
					BOOST_STATIC_ASSERT((mpl::equal<D, OtherD>::type::value));
					using f = factor<Unit, OtherUnit>;

					return quantity<T, D, Unit>{ x.value() - f::convertToTarget(y.value()) };
				}

			}
			// lambda expression = metafunction class or placeholder expression
			


			template <typename A, typename B>
			struct tester_metafunction
			{
				typedef  A type;

				constexpr A operator()(const A& _Left, const B& _Right) const
				{	
					return (_Left);
				}
			};
			// metafunction class (but useless)
			struct tester
			{
				template<typename A, typename B>
				struct apply
				{
					typedef typename tester_metafunction::type type;
				};
			};

			template< typename Dimension >
			struct extract_value
			{
				typedef Dimension type;		// return the dimension sequence (integral wrapper)
				
				template<size_t N>
				static int constexpr get()	// shouldn't this be executed at compile time??
				{
					return mpl::at_c<Dimension, N>::type::value;
				}
			};

			namespace Debug
			{
				template<size_t N>
				struct Decl;
			}

			template<typename OrigRatio>
			struct ratio_invert
			{
				typedef std::ratio<OrigRatio::den, OrigRatio::num> type;
			};

			template<typename Dimension, typename UnitFactors, size_t N>
			struct process_dimension_element
			{
				template<bool isNeg> struct helper;
			public:
				//Debug::Decl<N> n;
				static constexpr int value = mpl::at_c<Dimension, N>::type::value;
				typedef typename mpl::at_c<UnitFactors, N>::type factor;
				static constexpr bool isNegative = value < 0;

			private:
				static constexpr size_t abs_value = isNegative ? -value : value;
				static constexpr size_t multiplyBy = abs_value == 0 ? 1 : abs_value;
				template<bool isNeg>
				struct helper
				{
					typedef typename std::ratio<multiplyBy * factor::num, factor::den>::type type;
				};

				template<>
				struct helper<true>
				{
					typedef typename std::ratio<multiplyBy * factor::den, factor::num>::type type;
				};
			public:
				typedef typename helper<isNegative>::type type;
			};

			template<typename Dimension, typename UnitFactors, size_t N, size_t MAX>
			struct process_dimension
			{
				typedef typename process_dimension_element<Dimension, UnitFactors, N>::type		element;
				typedef typename process_dimension<Dimension, UnitFactors, N + 1, MAX>::container	next_container;

				typedef typename mpl::push_front<next_container, element>::type container;
			};

			template<typename Dimension, typename UnitFactors, size_t N>
			struct process_dimension<typename Dimension, typename UnitFactors, N, N>
			{
				typedef typename process_dimension_element<Dimension, UnitFactors, N>::type element;
				typedef mpl::vector<element>		container;
			};

			template<typename TargetUnits, typename SourceUnits, size_t N>
			struct process_ratio
			{
			public:
				//Debug::Decl<N> n;
				typedef typename mpl::at_c<TargetUnits, N>::type target_factor;
				typedef typename mpl::at_c<SourceUnits, N>::type source_factor;
				typedef std::ratio_divide<source_factor, target_factor>	this_ratio;


				typedef typename process_ratio<TargetUnits, SourceUnits, N - 1>::this_ratio	prev_ratio;

				typedef std::ratio_multiply<prev_ratio, this_ratio> accumulative_ratio;
			};

			template<typename TargetUnits, typename SourceUnits>
			struct process_ratio<TargetUnits, SourceUnits, 0>
			{
			public:
				//Debug::Decl<N> n;
				typedef typename mpl::at_c<TargetUnits, 0>::type		target_factor;
				typedef typename mpl::at_c<SourceUnits, 0>::type		source_factor;
				typedef std::ratio_divide<source_factor, target_factor>	this_ratio;

				typedef this_ratio accumulative_ratio;
			};


			// TODO!
			// both parameters are vectors of std::ratios
			template< class TargetUnits, class SourceUnits>
			struct complete_factor
			{
			private:
				typedef  ratio_divide<TargetUnits, SourceUnits> r;
			public:
				static constexpr long double convertToTarget(long double source)
				{
					return convert_helper< (r::num >= r::den) >::convert(source);
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
				template<> struct convert_helper<true>
				{
					static constexpr long double convert(long double source)
					{
						return (source * r::num) / r::den;
					}
				};
			};

			namespace SeparateSourceAndTargetUnits
			{

				template<typename Dimension, typename TargetUnits, typename SourceUnits, size_t N>
				struct process_dimension_element
				{
					template<bool isNeg> struct helper;
				public:
					//Debug::Decl<N> n;
					static constexpr int value = mpl::at_c<Dimension, N>::type::value;
					typedef typename mpl::at_c<TargetUnits, N>::type		target_unit;
					typedef typename mpl::at_c<SourceUnits, N>::type		source_unit;
					typedef std::ratio_divide<source_unit, target_unit>		factor;

					static constexpr bool isNegative = value < 0;

				private:
					static constexpr size_t abs_value = isNegative ? -value : value;
					static constexpr size_t multiplyBy = abs_value == 0 ? 1 : abs_value;
					template<bool isNeg>
					struct helper
					{
						typedef typename std::ratio<multiplyBy * factor::num, factor::den>::type type;
					};

					template<>
					struct helper<true>
					{
						typedef typename std::ratio<multiplyBy * factor::den, factor::num>::type type;
					};
				public:
					typedef typename helper<isNegative>::type type;
				};

				template<typename Dimension, typename TargetUnits, typename SourceUnits, size_t N, size_t MAX>
				struct process_dimension
				{
					typedef typename process_dimension_element<Dimension, TargetUnits, SourceUnits, N>::type		element;
					typedef typename process_dimension<Dimension, TargetUnits, SourceUnits, N + 1, MAX>::container	next_container;

					typedef typename mpl::push_front<next_container, element>::type container;
				};

				template<typename Dimension, typename TargetUnits, typename SourceUnits, size_t N>
				struct process_dimension<typename Dimension, typename TargetUnits, typename SourceUnits, N, N>
				{
					typedef typename process_dimension_element<Dimension, TargetUnits, SourceUnits, N>::type element;
					typedef mpl::vector<element>		container;
				};

				template<typename RatioSequence, size_t N>
				struct ratio_sequence_multiply
				{
					//friend ratio_sequence_multiply<RatioSequence, 0>;
					//friend ratio_sequence_multiply<RatioSequence, N - 1>;


				//private:
					typedef typename mpl::at_c<RatioSequence, N>::type this_ratio;
					typedef typename ratio_sequence_multiply<RatioSequence, N - 1>::accumulative_ratio	prev_ratio;

				public:
					//Debug::Decl<N> n;
					typedef std::ratio_multiply<prev_ratio, this_ratio> accumulative_ratio;
				};

				template<typename RatioSequence>
				struct ratio_sequence_multiply<RatioSequence, 0>
				{
				//private:
					typedef typename mpl::at_c<RatioSequence, 0>::type this_ratio;
				public:
					//Debug::Decl<N> n;

					typedef this_ratio accumulative_ratio;
				};

				namespace NoIntegrals
				{
//					typedef typename SeparateSourceAndTargetUnits::process_dimension<velocity, TargetUnits, SourceUnits, 0, 6>::container a_container;

					//process_dimension<ResDimension, UnitsForA, UnitsForB, 0, mpl::size<ResDimension>::value - 1>::container

					template<typename Dimension, typename UnitsForA, typename UnitsForB>
					struct process_dimension_into_unit_container
					{
						typedef typename process_dimension<Dimension, UnitsForA, UnitsForB, 0, mpl::size<Dimension>::value - 1>::container container;
					};
					////////////////////////////////////////////////////////////////////////////////////////////////////
					/// <summary>	Process dimension into an accumulative ratio. </summary>
					///
					/// <remarks>	Juan Dent, 16/3/2017. </remarks>
					///
					/// <typeparam name="T">		  	Represents the base type whose value we manipulate (usually long double). </typeparam>
					/// <typeparam name="Dimension">  	Type of the dimension, e.g. velocity </typeparam>
					/// <typeparam name="TargetUnits">	Sequence of target units in std::ratio format. </typeparam>
					/// <typeparam name="SourceUnits">	Sequence of source units in std::ratio format. </typeparam>
					////////////////////////////////////////////////////////////////////////////////////////////////////

					template<typename T, typename Dimension, typename TargetUnits, typename SourceUnits>
					struct process_dimension_into_ratio
					{
					private:
						typedef typename process_dimension<Dimension, TargetUnits, SourceUnits, 0, mpl::size<Dimension>::value - 1>::container container;
					public:
						typedef typename ratio_sequence_multiply<container, mpl::size<container>::value -1 >::accumulative_ratio				ratio;
					public:
						//typedef process_dimension_into_ratio<T, Dimension, TargetUnits, SourceUnits>											type;

						static constexpr T get(T value)
						{
							return ratio::num * value / ratio::den;
						}

					};

					namespace Detail
					{
						////////////////////////////////////////////////////////////////////////////////////////////////////
						/// <summary>	Format unit that comes as a std::ratio </summary>
						///
						/// <remarks>	Juan Dent, 16/3/2017. </remarks>
						///
						/// <typeparam name="Unit">	Type of the unit. </typeparam>
						////////////////////////////////////////////////////////////////////////////////////////////////////

						template<typename Ratio>
						std::string formatRatio()
						{
							ostringstream os{};
							os << Ratio::num << ":" << Ratio::den;
							auto s = os.str();
							return s;
						}


						template<typename UnitsAsFactors, size_t N>
						struct units_as_string
						{
						private:
							typedef typename mpl::at_c<UnitsAsFactors, N>::type unit;
						public:
							static std::string getName()
							{
								auto s = units_as_string<UnitsAsFactors, N - 1>::getName();
								s += ", ";
								s += formatRatio<unit>();
								return s;
							}
						};

						template<typename UnitsAsFactors>
						struct units_as_string<UnitsAsFactors, 0>
						{
						private:
							typedef typename mpl::at_c<UnitsAsFactors, 0>::type unit;
						public:
							static std::string getName()
							{
								auto s = formatRatio<unit>();
								return s;
							}
						};

						template<typename UnitsAsFactors>
						struct all_units_as_string
						{
							typedef units_as_string<UnitsAsFactors, mpl::size<UnitsAsFactors>::value - 1> type;
						};

						////////////////////////////////////////////////////////////////////////////////////////////////////
						/// <summary>	Produce a string with the dimension elements. </summary>
						///
						/// <remarks>	Juan Dent, 16/3/2017. </remarks>
						///
						/// <typeparam name="Dimension">	Type of the dimension. </typeparam>
						////////////////////////////////////////////////////////////////////////////////////////////////////

						template<typename Dimension, size_t N>
						struct dimension_elements_as_string
						{
							static int constexpr element_value = mpl::at_c<Dimension, N>::type::value;

							static std::string getName()
							{
								// display int as a string
								auto s = dimension_elements_as_string<Dimension, N - 1>::getName();
								s += ", ";
								s += std::to_string(element_value);
								return s;
							}

						};

						template<typename Dimension>
						struct dimension_elements_as_string<Dimension,0>
						{
							static int constexpr element_value = mpl::at_c<Dimension, 0>::type::value;

							static std::string getName()
							{
								// display int as a string
								auto s = std::to_string(element_value);
								return s;
							}

						};

						template<typename Dimension>
						struct dimension_as_string
						{
							typedef dimension_elements_as_string<Dimension, mpl::size<Dimension>::value - 1> type;
						};

						////////////////////////////////////////////////////////////////////////////////////////////////////
						/// <summary>	A verify units. </summary>
						///
						/// <remarks>	Juan Dent, 16/3/2017. 
						/// 			If pos x of the dimension is 0, then the 
						/// 			corresponding unit must be unity (1:1)
						/// 			</remarks>
						///
						/// <typeparam name="Dimension">	Type of the dimension. </typeparam>
						/// <typeparam name="Units">		Type of the units. </typeparam>
						////////////////////////////////////////////////////////////////////////////////////////////////////

						template<typename Dimension, typename Units, size_t N>
						struct verify_units
						{
							static constexpr int dim_element_value = mpl::at_c<Dimension, N>::type::value;
							typedef typename mpl::at_c<Units, N>::type	unit;
							static constexpr bool is_valid = (dim_element_value != 0 || (dim_element_value == 0 && unit::num == 1 && unit::den == 1)) && verify_units<Dimension, Units, N-1>::is_valid;

							static_assert(is_valid, "Dimensions whose elements are cero, must have corresponding unit to be 1:1!");
						};

						template<typename Dimension, typename Units>
						struct verify_units<Dimension, Units, 0>
						{
							static constexpr int dim_element_value = mpl::at_c<Dimension,0>::type::value;
							typedef typename mpl::at_c<Units, 0>::type	unit;
							static constexpr bool is_valid = (dim_element_value != 0 || (dim_element_value == 0 && unit::num == 1 && unit::den == 1));

							static_assert(is_valid, "Dimensions whose elements are cero, must have corresponding unit to be 1:1!");
						};

						template<typename Dimension, typename Units>
						struct verify_all_units
						{
							static constexpr bool is_valid = verify_units<Dimension, Units, mpl::size<Dimension>::value - 1>::is_valid;
						};

					}


					template <class T, class Dimension, class /*Units*/ TargetUnits>
					struct Quantity
					{
						//static_assert(Detail::verify_all_units<Dimension, TargetUnits>::is_valid, "At least one element of Dimensions is cero, and yet the corresponding unit is not 1:1!");
						const bool is_valid = Detail::verify_all_units<Dimension, TargetUnits>::is_valid;


						template<class T, class OtherD, class SourceUnits>
						friend	struct Quantity;

						explicit Quantity(T x)
						{
							m_value = x;
						}
						T value() const { return m_value; }


						static std::string unitsAsText()
						{
							return Detail::all_units_as_string<TargetUnits>::type::getName();
						}


						template<class T, class OtherDim, class SourceUnits>
						Quantity& operator+= (Quantity<T, OtherDim, SourceUnits> rhs)
						{
							static_assert(mpl::equal<Dimension, OtherDim>::value, "dimensions much match");
							using f = process_dimension_into_ratio<T, Dimension, TargetUnits, SourceUnits>::type;
							auto rhs_factored = f::get(rhs.m_value);
							m_value += rhs_factored;
							return *this;
						}
					private:
						T m_value;
					};

					template<typename T, typename Dimension, typename TargetUnits, typename OtherDim, typename SourceUnits>
					Quantity<T, Dimension, TargetUnits>
						operator+(Quantity<T, Dimension, TargetUnits> x, Quantity<T, OtherDim, SourceUnits> y)
					{
						static_assert(mpl::equal<Dimension, OtherDim>::value, "dimensions much match for addition");
						using f = process_dimension_into_ratio<T, Dimension, TargetUnits, SourceUnits>::type;

						return quantity<T, Dimension, TargetUnits>{ x.value() + f::get(y.value()) };
					}
					template<typename T, typename Dimension, typename TargetUnits, typename OtherDim, typename SourceUnits>
					Quantity<T, Dimension, TargetUnits>
						operator-(Quantity<T, Dimension, TargetUnits> x, Quantity<T, OtherDim, SourceUnits> y)
					{
						static_assert(mpl::equal<Dimension, OtherDim>::value, "dimensions much match for subtraction");
						using f = process_dimension_into_ratio<T, Dimension, TargetUnits, SourceUnits>::type;

						return quantity<T, Dimension, TargetUnits>{ x.value() - f::get(y.value()) };
					}

					namespace Detail
					{
						////////////////////////////////////////////////////////////////////////////////////////////////////
						/// <summary>	The plus_f metafunction class </summary>
						///
						/// <remarks>	Juan Dent, 16/3/2017. </remarks>
						////////////////////////////////////////////////////////////////////////////////////////////////////

						struct plus_f
						{
							template<typename A, typename B>
							struct apply
							{
								typedef typename mpl::plus<A, B>::type type;
							};
						};
					}
					////////////////////////////////////////////////////////////////////////////////////////////////////
					/// <summary>	Multiplication operator. </summary>
					///
					/// <remarks>	Juan Dent, 16/3/2017. </remarks>
					///
					/// <typeparam name="T">		  	Numeric type. </typeparam>
					/// <typeparam name="Dimension">  	Type of dimension 1. </typeparam>
					/// <typeparam name="TargetUnits">	Type of the target units. </typeparam>
					/// <typeparam name="OtherDim">   	Type of dimension 2. </typeparam>
					/// <typeparam name="SourceUnits">	Type of the source units. </typeparam>
					/// <param name="x">	The Quantity&lt;T,Dimension,TargetUnits&gt; to process. </param>
					/// <param name="y">	The Quantity&lt;T,OtherDim,SourceUnits&gt; to process. </param>
					///
					/// <returns>	The result of the operation. </returns>
					////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
					template<typename T, typename Dimension_A, typename Units_A, typename Dimension_B, typename Units_B, 
						typename ResDimension = typename mpl::transform<Dimension_A, Dimension_B, mpl::plus<_1, _2>>::type,
						typename ResUnits = typename process_dimension_into_ratio<T, ResDimension, Units_A, Units_B>::type>
					Quantity<T, Dimension_A, Units_A>
					
					operator*(Quantity<T, Dimension_A, Units_A> x, Quantity<T, Dimension_B, Units_B> y)
					{
						auto name = Detail::all_units_as_string<ResUnits>::type::getName();
						cout << name << endl;

						auto x_transformed = ResUnits::get(x.value());
						auto y_transformed = ResUnits::get(y.value());
						return Quantity<T, Dimension_A, Units_A>{ x_transformed * y_transformed};
					}
#endif
				}
			}

			void useLength()
			{
				using namespace ::Chapter3::Questions::Q3_8::AddingUnitsToQuantity;

				// velocity given using base units:
				typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;         // l/t
				typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;


				typedef ratio<1, 1>							unity;
				typedef mpl::vector<unity, mm, msec, unity, unity, unity, unity> TargetUnits;
				typedef mpl::vector<unity, m, sec, unity, unity, unity, unity> SourceUnits;

#if 0
				SeparateSourceAndTargetUnits::NoIntegrals::Quantity<long double, velocity, TargetUnits> q{ 4.5 };
				SeparateSourceAndTargetUnits::NoIntegrals::Quantity<long double, velocity, SourceUnits> o{ 4.5 };

				q += o;

				cout << o.value() << ", " <<   q.value() << endl;
#endif
#if 1
				typedef mpl::vector<unity, cm, msec, unity, unity, unity, unity> UnitsForA;
				typedef mpl::vector<kg, unity, unity, unity, unity, unity, unity>  UnitsForB;

				SeparateSourceAndTargetUnits::NoIntegrals::Quantity<long double, velocity, UnitsForA>	qq{ 4.5 };
				SeparateSourceAndTargetUnits::NoIntegrals::Quantity<long double, mass, UnitsForB>		oo{ 4.5 };

				cout << "qq: " << qq.unitsAsText() << endl;
				cout << "oo: " << oo.unitsAsText() << endl;

				typedef typename mpl::transform<velocity, mass, mpl::plus<_1, _2>>::type velocity_times_mass;

				//auto name = SeparateSourceAndTargetUnits::NoIntegrals::Detail::dimension_elements_as_string<velocity_times_mass, 2>::element_value; //   ::type::getName();

				auto name = SeparateSourceAndTargetUnits::NoIntegrals::Detail::dimension_as_string<velocity_times_mass>::type::getName();
#if 1
				{
#if 0
					template<typename T, typename Dimension_A, typename Units_A, typename Dimension_B, typename Units_B,
						typename ResDimension = typename mpl::transform<Dimension_A, Dimension_B, mpl::plus<_1, _2>>::type,
						typename ResUnits = typename process_dimension_into_unit_container<ResDimension, Units_A, Units_B>::type>
						Quantity<T, Dimension_A, Units_A>

						operator*(Quantity<T, Dimension_A, Units_A> x, Quantity<T, Dimension_B, Units_B> y)
					{
						auto name = Detail::all_units_as_string<ResUnits>::type::getName();
						cout << name << endl;

						auto x_transformed = ResUnits::get(x.value());
						auto y_transformed = ResUnits::get(y.value());
						return Quantity<T, Dimension_A, Units_A>{ x_transformed * y_transformed};
					}
#endif
					auto vel_dimension_as_str = SeparateSourceAndTargetUnits::NoIntegrals::Detail::dimension_as_string<velocity>::type::getName();
					auto mass_dimension_as_str = SeparateSourceAndTargetUnits::NoIntegrals::Detail::dimension_as_string<mass>::type::getName();

					typedef typename mpl::transform<velocity, mass, mpl::plus<_1, _2>>::type  ResDimension;
					auto res_dimension_as_str = SeparateSourceAndTargetUnits::NoIntegrals::Detail::dimension_as_string<ResDimension>::type::getName();

					cout << "(" << vel_dimension_as_str << ") + (" << mass_dimension_as_str << ") = (" << res_dimension_as_str << ")" << endl;

					
					////////////////////////////////////////////////////////////////////////////////////////////////////
					/// <summary>	Defines an alias representing the accumulative ratio given a dimension
					/// 			and 2 sets of units. </summary>
					///
					/// <remarks>	Juan Dent, 17/3/2017. 
					/// 			Vital: access ratio instead of type!!
					/// 			</remarks>
					////////////////////////////////////////////////////////////////////////////////////////////////////

					typedef SeparateSourceAndTargetUnits::NoIntegrals::process_dimension_into_ratio<long double, ResDimension, UnitsForA, UnitsForB>::ratio ratio_accum;
					ratio_accum rac;

					cout << "accumulative ratio = " << ratio_accum::num << ":" << ratio_accum::den << endl;

					auto all_units_for_A = SeparateSourceAndTargetUnits::NoIntegrals::Detail::all_units_as_string<UnitsForA>::type::getName();
					auto all_units_for_B = SeparateSourceAndTargetUnits::NoIntegrals::Detail::all_units_as_string<UnitsForB>::type::getName();


					typedef typename SeparateSourceAndTargetUnits::NoIntegrals::process_dimension_into_unit_container<ResDimension, UnitsForA, UnitsForB>::container a_container_of_units;
					a_container_of_units ac;

					auto all_units_in_container = SeparateSourceAndTargetUnits::NoIntegrals::Detail::all_units_as_string<a_container_of_units>::type::getName();

					cout << "units for A = (" << all_units_for_A << ")\nunits for B = (" << all_units_for_B << ")\nunits using ResDimension = (" << all_units_in_container << ")" << endl;

					typedef SeparateSourceAndTargetUnits::process_dimension_element<ResDimension, UnitsForA, UnitsForB, 1>::type		element;
					element ee;

					typedef SeparateSourceAndTargetUnits::process_dimension<ResDimension, UnitsForA, UnitsForB, 6, 6>::container cont_of_units;


					cout << "stop" << endl;

					//typedef SeparateSourceAndTargetUnits::ratio_sequence_multiply<
					
					//auto all_units = SeparateSourceAndTargetUnits::NoIntegrals::Detail::units_as_string<ResUnits, 0>::getName();

					//using namespace ::Chapter3::Questions::Q3_8::SeparateSourceAndTargetUnits::NoIntegrals;

					//auto xx = qq * oo;
				}
				//cout << xx.value() << ", " << oo.value() << endl;
#endif
				cout << oo.unitsAsText() << endl;

#endif

				typedef typename SeparateSourceAndTargetUnits::process_dimension_element<velocity, TargetUnits, SourceUnits, 1>::type dim_1;
																				   
																				   // calculate each element of velocity using the new units:
				cout << 1 << ": " << dim_1::num << " " << dim_1::den << endl;		// cm --> mm (x 10)

				// dim 1: cm -> mm = x 10
				// dim 2: sec -> msec = % 1000

				typedef typename SeparateSourceAndTargetUnits::process_dimension_element<velocity, TargetUnits, SourceUnits, 2>::type dim_2;

				cout << 2 << ": " << dim_2::num << " " << dim_2::den << endl;		// sec --> msec = % 1000


				typedef typename SeparateSourceAndTargetUnits::process_dimension<velocity, TargetUnits, SourceUnits, 0, mpl::size<velocity>::value - 1>::container a_container;


				//typedef typename SeparateSourceAndTargetUnits::process_dimension<velocity, TargetUnits, SourceUnits, 0, 6>::container a_container;
				a_container a_c;

				typedef typename mpl::at_c<a_container, 0>::type ratio_0;
				cout << ratio_0::num << ":" << ratio_0::den << endl;

				typedef typename mpl::at_c<a_container, 1>::type ratio_1;
				cout  << ratio_1::num << ":" << ratio_1::den << endl;

				typedef typename mpl::at_c<a_container, 2>::type ratio_2;
				cout << ratio_2::num << ":" << ratio_2::den << endl;

				typedef typename mpl::at_c<a_container, 3>::type ratio_3;
				cout << ratio_3::num << ":" << ratio_3::den << endl;

				typedef typename mpl::at_c<a_container, 4>::type ratio_4;
				cout << ratio_4::num << ":" << ratio_4::den << endl;

				typedef typename mpl::at_c<a_container, 5>::type ratio_5;
				cout << ratio_5::num << ":" << ratio_5::den << endl;

				typedef typename mpl::at_c<a_container, 6>::type ratio_6;
				cout << ratio_6::num << ":" << ratio_6::den << endl;


				typedef typename SeparateSourceAndTargetUnits::ratio_sequence_multiply<a_container, 6>::accumulative_ratio accumulative_ratio;

				cout << "accum ratio : " << accumulative_ratio::num << " : " << accumulative_ratio::den << endl;		// sec --> msec = % 1000

				typedef SeparateSourceAndTargetUnits::NoIntegrals::process_dimension_into_ratio<long double, velocity, TargetUnits, SourceUnits> final_ratio;
				auto units_changed = final_ratio::get(4.55);

#if 0
				//  this creates a container whose elements are std::ratio and their values should be multipled to the long double value of the quantity
				typedef typename process_dimension<velocity, vec_conv_factors, 0, mpl::size<velocity>::value - 1>::container container;
				container cont;
#endif
				// some lengths factors:
				typedef ConversionFactor<mm, m>::type		mm_to_m;					// 1/1000
				typedef ConversionFactor<mm, cm>::type		mm_to_cm;					// 1/10

																						// some time factors:
				typedef ConversionFactor<msec, sec>::type	msec_to_sec;				// 1/1000
				typedef ConversionFactor<msec, csec>::type	msec_to_csec;				// 1/10


				cout << mm_to_m::num << " " << mm_to_m::den << endl;

				// create a vector of convertion factors:
				typedef mpl::vector<unity, mm_to_m, msec_to_sec, unity, unity, unity, unity> vec_conv_factors;
				typedef mpl::vector<unity, mm_to_m, msec_to_sec, unity, unity, unity, unity> vec_conv_factors;




				auto v1 = mpl::at_c<velocity, 1>::type::value;	// => 1
				auto v2 = mpl::at_c<velocity, 2>::type::value;	// => -1
#if 0
				typedef extract_value<velocity> vel_extractor;
				auto v3 = vel_extractor::get<1>();
				auto v4 = vel_extractor::get<2>();
#endif

				typedef typename mpl::at_c<vec_conv_factors, 1>::type f1 ;
				typedef typename mpl::at_c<vec_conv_factors, 2>::type f2;
				typedef typename mpl::at_c<vec_conv_factors, 3>::type f3;

				cout << mpl::size<velocity>::type::value << endl;

				// calculate each element of velocity using the new units:
				typedef typename process_dimension_element<velocity, vec_conv_factors,0>::type dim0;
				cout << 0 << ": " << dim0::num << " " << dim0::den  << endl;

				//  this creates a container whose elements are std::ratio and their values should be multipled to the long double value of the quantity
				typedef typename process_dimension<velocity, vec_conv_factors, 0, mpl::size<velocity>::value-1>::container container;
				container cont;

				static_assert(std::is_same<  mpl::at_c<container, 1>::type, mm_to_m>::value, "");

				// mix both sequences velocity and vec_conv_factors!! TODO

				///velocity vel;
				vec_conv_factors v_fac;

				// we have a quantity, and we want to change the units of it (but not its dimension!)
				//quantity<long double, velocity

				typedef typename mpl::lambda < tester_metafunction<_1, _2>>::type tester_metafunction_class;

#if 0
				typedef mpl::transform<
					velocity,
					tester_metafunction_class,
					mpl::back_inserter< vec_conv_factors >
				>::type vel;

				vel v;
#endif

				quantity<long double, length, mm> l_mm{ 4.5 };
				quantity<long double, length, m>  l_m{ 4.24 };

				l_mm += l_m;


				auto res = l_mm + l_m;

				auto res2 = res - l_m;


				typedef mpl::transform<
					mpl::range_c<int, 0, 10>
					, mpl::plus<_1, _1>
					, mpl::front_inserter /* back_inserter*/ < mpl::vector0<> >
				>::type result;

				result transform_r;

				typedef mpl::reverse_copy<
					mpl::range_c<int, 0, 5>
					, mpl::front_inserter< mpl::vector_c<int, 5, 6, 7, 8, 9> >
				>::type range;

				range r_copy;

				typedef mpl::reverse_copy<
					mpl::range_c<int, 0, 5>
					, mpl::back_inserter< mpl::vector_c<int, 5, 6, 7, 8, 9> >
				>::type range_rev_back;

				range_rev_back r_back_copy;


				typedef mpl::copy<
					mpl::range_c<int, 0, 5>
					, mpl::front_inserter< mpl::vector_c<int, 5, 6, 7, 8, 9> >
				>::type range_down_up;

				range_down_up dup;


				typedef mpl::copy<
					mpl::range_c<int, 0, 5>
					, mpl::back_inserter< mpl::vector_c<int, 5, 6, 7, 8, 9> >
				>::type range_up_down;

				range_up_down rup;


				// length a in mm * length b in inches
				// dim = plus_f<D1,D2>
				// a + factor<mm, in>::convert(b)
				// for each dimension

				typedef  ratio_divide<cm, mm> r;

				auto valinum = 15.0;
				valinum *= r::den;
				valinum /= r::num;
				cout << valinum << endl;

				//cout << factor<cm, mm>::convert(15) << endl;
				//cout << (in < cm) << endl;

				cout << factor<in, cm>::convertToTarget(25.4) << endl;

				//cout << factor_using_enable_if<in, cm>::convertToSmaller(25.4) << endl;


				//cout << factor_using_tag_dispatch<in, cm>::convertToSmaller(25.4) << endl;

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
			struct twice : apply1<F, typename apply1<F, X>::type>
			{};

			// now thrice (f(f(x))) -- where f is a metafunction class:
			template <typename F, typename X>
			struct thrice : apply1<F, typename apply1<F, typename apply1<F, X>::type>::type>
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

					template<typename C1, typename C2 = void, typename C3 = void>
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
				struct lambda<F<_1, _2>>		// matches mpl::plus<_1,_2>
				{
					typedef lambda<F<_1, _2>> type;

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
				struct apply<F<_1, _2>, Args...> : lambda<F<_1, _2>>::template apply<Args...>
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
					struct apply : mpl::plus<T1, T2>
					{};
				};

				struct common_f
				{
					template <typename T1, typename T2>
					struct apply : std::common_type<T1, T2>
					{
						typedef typename std::common_type<T1, T2>::type type;
					};
				};

				template<typename T1, typename T2>
				struct common_type_metafunction : std::common_type<T1, T2>
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

					typedef typename apply<common_type_metafunction<_1, _2>, float, long>::type common_type;
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


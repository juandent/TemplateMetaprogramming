#include "stdafx.h"
#include <type_traits>
#include <utility>
#include <boost\mpl/apply.hpp>
#include <boost\mpl\plus.hpp>
#include <boost\mpl\int.hpp>
#include <boost\mpl/lambda.hpp>

//template <typename MetaFn, typename ...Args, std::enable_if<typedef template MetaFn::apply<Args...>::type>>
//struct lambda
//{

//};
// 
using namespace std;
namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;


// has variadic template apply
template <typename T, typename ...Args> struct has_variadic_template_apply
{
	template<typename U>
	static std::true_type test(U&, typename T::template apply<Args...>* = nullptr) { return true; }

	static std::false_type test(...) { return false; }

	using type = decltype(test( declval<T>()));
	constexpr static bool value = type{};
};

template <typename T, typename A1> struct has_unary_template_apply
{
	template<typename U>
	static std::true_type test(U&, typename T::template apply<A1>* = nullptr) { return true; }

	static std::false_type test(...) { return false; }

	using type = decltype(test(declval<T>()));
	constexpr static bool value = type{};
};

template <typename T, typename A1, typename A2> struct has_binary_template_apply
{
	template<typename U>
	static std::true_type test(U&, typename T::template apply<A1,A2>::type* = nullptr) { return true; }

	static std::false_type test(...) { return false; }

	using type = decltype(test(declval<T>()));
	constexpr static bool value = type{};
};

#if 1
template<typename T> struct has_template_apply
{
	using bin_type = typename has_binary_template_apply<T, mpl::int_<2>, mpl::int_<8>>::type;
	constexpr static bool bin_value = bin_type{};

//	template<typename U>
//	static std::true_type test_bin(U&, has_binary_template_apply<T, mpl::int_<2>, mpl::int_<6>>* nullptr) { return true; }

//	static std::false_type test_bin(...) { return false; }

//	using type_bin = decltype(test_bin(declval<T>()));
//	constexpr static bool value_bin = type{};

	//constexpr static bool bin_value = has_binary_template_apply<T, void, void>::value;
	//constexpr static bool una_value = has_unary_template_apply<T, void>::value;
	//constexpr static bool var_value = has_variadic_template_apply<T>::value;

	//sconstexpr static bool value = bin_value || una_value || var_value;
};
#endif
struct plus_f
{
	template<class T1, class T2>
	struct apply
	{
		typedef typename mpl::plus<T1, T2>::type type;
	};
};

struct plus_no_metafunction_class
{
};

void doTest()
{
	constexpr bool _has = has_template_apply<plus_f>::bin_value;
	//constexpr bool _has_w_arg = has_binary_template_apply<plus_f, void, void>::value;	

	//constexpr bool _hasnot = has_template_apply<plus_no_metafunction_class>::value;
}

template<typename MetaFn, typename ...Args>
struct twice : mpl::apply<MetaFn, typename mpl::apply<MetaFn,Args...>::type>
{};


typedef typename twice<boost::add_pointer<_>, double>::type twice_double;

typedef mpl::apply<_1, mpl::apply<_1, _2>>::type lambda_expression_twice;

//typedef mpl::apply<

//typedef mpl::apply< lambda_expression_twice, boost::add_rvalue_reference<int>, int>	inter;


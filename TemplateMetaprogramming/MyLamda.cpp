#include "stdafx.h"
#include <type_traits>
#include <boost\mpl\plus.hpp>
#include <boost\mpl\int.hpp>

//template <typename MetaFn, typename ...Args, std::enable_if<typedef template MetaFn::apply<Args...>::type>>
//struct lambda
//{

//};
namespace mpl = boost::mpl;

namespace detail {
#if 0
	template <typename MetaFn, typename ...Args>
	using result = MetaFn::apply<Args...>::type;
	struct is_metafunction_class_impl : mpl::true_
	{};
#endif
#if 0
	template <typename MetaFn, typename ...Args>
	constexpr bool is_metafunction_class_impl()
	{
		return false;
	};
#endif
}

#if 1
template<typename MetaFn, typename A1, typename A2, typename A = typedef template MetaFn::apply<A1,A2>::type>
struct test
{
	constexpr static int value = 1;
	typedef A type;
};

template<typename MetaFn, typename A1, typename A2>
struct test
{
	constexpr static int value = 2;
	typedef A type;
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
	//const expr int value = detail::is_metafunction_class_impl<plus_f, mpl::int_<3>, mpl::int_<8>>();

//	typedef 		test<plus_f, mpl::int_<3>, mpl::int_<6>>::type plus_type;
//	constexpr int _value_2 = test<plus_no_metafunction_class, mpl::int_<3>, mpl::int_<9>>::value;
	
}


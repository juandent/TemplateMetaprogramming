#include "stdafx.h"
#include <type_traits>
#include <utility>
#include <boost\mpl\plus.hpp>
#include <boost\mpl\int.hpp>

//template <typename MetaFn, typename ...Args, std::enable_if<typedef template MetaFn::apply<Args...>::type>>
//struct lambda
//{

//};
// 
using namespace std;
namespace mpl = boost::mpl;

template <typename T, typename ...Args> struct has_template_apply
{
	template<typename U>
	static std::true_type test(U&, typename T::template apply<Args...>* = nullptr) { return true; }

	static std::false_type test(...) { return false; }

	using type = decltype(test( declval<T>()));
	constexpr static bool value = type{};
};


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
	constexpr bool _has = has_template_apply<plus_f, void>::value;
	constexpr bool _hasnot = has_template_apply<plus_no_metafunction_class, void>::value;
}


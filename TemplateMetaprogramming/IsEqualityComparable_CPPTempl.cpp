#include "stdafx.h"


#include <utility>        // for declval()
#include <type_traits>    // for true_type and false_type

template<typename T>
class IsEqualityComparable
{
private:
	// test convertibility of == and ! == to bool:
	static void* conv(bool);  // to check convertibility to bool
	template<typename U>
	static std::true_type test(decltype(conv(std::declval<U const&>() ==
		std::declval<U const&>())),
		decltype(conv(!(std::declval<U const&>() ==
			std::declval<U const&>())))
	);
	// fallback:
	template<typename U>
	static std::false_type test(...);
public:
	static constexpr bool value = decltype(test<T>(nullptr,
		nullptr))::value;

#define JDH
#ifdef JDH
	// arguments of decltype are not evaluated! Only their type is taken (i.e. void*)
	// thus static conv(bool) does not need to be defined nor static test
	template<typename U>
	using type = decltype(conv(std::declval<U const&>() == std::declval<U const&>()));
#endif
};


class XT
{
	int a, b;
public:
	XT(int a, int b) : a{ a }, b{ b } {}

	friend bool operator==(XT const& lhs, XT const& rhs)
	{
		return lhs.a == rhs.a && lhs.b == rhs.b;
	}
};


void useEqualityComparable()
{
	using res = IsEqualityComparable<XT>::template type<XT>;
	res* pRes;
	constexpr bool hasEqualOperator = IsEqualityComparable<XT>::value;
	bool has = hasEqualOperator;
}
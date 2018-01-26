#include "stdafx.h"

#include <type_traits>


template <bool>
struct not_impl;

template <>
struct not_impl<true>
{
	using type = std::false_type;
};

template <>
struct not_impl<false>
{
	using type = std::true_type;
};

template <template <typename> class Predicate, typename... T>
using not_t = typename not_impl<Predicate<T>::value...>::type;


template<typename T>
struct IsIntegral
{
	static constexpr bool value = std::is_integral<T>::value;
};

//using not_integrals = not_t<IsIntegral, int, float>;	// ERROR

using not_integrals = not_t<IsIntegral, int>;	// OK



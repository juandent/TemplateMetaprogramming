#include "stdafx.h"

using std::begin;
using std::end;

namespace is_iterable_internal
{
	using std::begin;
	using std::end;

	template<typename T>
	struct is_iterable
	{
		template<typename U>
		static constexpr auto is_iterable_impl(int) -> decltype(
			begin(std::declval<U&>()) != end(std::declval<U&>()),
			void(),
			++std::declval<decltype(begin(std::declval<U&>()))&>(),
			void(*begin(std::declval<U&>())),
			std::true_type{}
			)
		{
			return std::true_type{};
		}

		template<typename U>
		static constexpr std::false_type is_iterable_impl(...)
		{
			return std::false_type{ };
		}

		using type = decltype(is_iterable_impl<T>(0));
	};
}

template<typename T>
struct is_iterable
{
	static constexpr bool value = is_iterable_internal::is_iterable<T>::type::value;
};

template<typename Container>
typename std::enable_if<is_iterable<Container>::value, void>::type
do_something( const Container& xs)
{
	for (auto x : xs)
		std::cout << x << std::endl;
}

template<typename U>
struct Test
{
	using type = decltype(
		begin(std::declval<U&>()) != end(std::declval<U&>()),
		void(),
		++std::declval<decltype(begin(std::declval<U&>()))&>(),
		void(*begin(std::declval<U&>())),
		std::true_type{}
	);
};
void useIsIterable()
{
	std::vector<int> v = { 2,3,5,7 };
	do_something(v);

	int n = 42;
	constexpr bool ok = is_iterable<decltype(n)>::value;

	using t = Test<decltype(v)>::type;

	constexpr bool is = std::is_same<t, std::true_type>::value;

	// using dt = decltype(do_something(n));

	auto p = std::make_pair(3.14159, -7);
	// do_something(p);

}

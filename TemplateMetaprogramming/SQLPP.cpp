#include "stdafx.h"

#include <type_traits>


namespace sqlpp
{
	struct consistent_t : std::true_type
	{
	};
}  // namespace sqlpp



namespace sqlpp
{
#define SQLPP_PORTABLE_STATIC_ASSERT(name, message) \
  struct name : std::false_type                     \
  {                                                 \
    template <typename... T>                        \
    explicit name(T&&...)                           \
    {                                               \
      static_assert(wrong_t<T...>::value, message); \
    }                                               \
    auto begin() const -> void;                     \
    auto end() const -> void;                       \
  }

	namespace detail
	{
		template <bool Consistent, typename Assert>
		struct static_check_impl
		{
			using type = Assert;
		};

		template <typename Assert>
		struct static_check_impl<true, Assert>
		{
			using type = consistent_t;
		};
	}  // namespace detail

	template <bool Consistent, typename Assert>
	using static_check_t = typename detail::static_check_impl<Consistent, Assert>::type;

	namespace detail
	{
		template <typename... StaticChecks>
		struct static_combined_check_impl;

		template <typename StaticCheck, typename... Rest>
		struct static_combined_check_impl<StaticCheck, Rest...>
		{
			using type = StaticCheck;
		};

		template <typename... Rest>
		struct static_combined_check_impl<consistent_t, Rest...>
		{
			using type = typename static_combined_check_impl<Rest...>::type;
		};

		template <>
		struct static_combined_check_impl<>
		{
			using type = consistent_t;
		};
	}  // namespace detail

	template <typename... StaticChecks>
	using static_combined_check_t = typename detail::static_combined_check_impl<StaticChecks...>::type;
}  // namespace sqlpp


using namespace sqlpp;

//SQLPP_PORTABLE_STATIC_ASSERT
#include "stdafx.h"

#if 0

struct statement_policy
{

};









template<typename Db, typename...Policies>
struct statement_t : public Policies::template _base_t<detail::statement_policies_t<Db, Policies...>>...
{

};


////////////////////////////////
namespace sqlpp
{
	template <typename ValueType>
	struct bad_expression
	{
		template <typename... T>
		bad_expression(T&&... /*unused*/)
		{
		}
		using _traits = make_traits<ValueType, tag::is_expression>;
		using _nodes = detail::type_vector<>;
	};

	namespace detail
	{
		template <bool Enable, template <typename Lhs, typename... Rhs> class Expr, typename Lhs, typename... Rhs>
		struct in_expression_impl
		{
			using type = bad_expression<boolean>;
		};

		template <template <typename Lhs, typename... Rhs> class Expr, typename Lhs, typename... Rhs>
		struct in_expression_impl<true, Expr, Lhs, Rhs...>
		{
			using type = Expr<Lhs, Rhs...>;
		};
	}  // namespace detail
	template <typename Check, template <typename Lhs, typename... Rhs> class Expr, typename Lhs, typename... Rhs>
	using in_expression_t = typename detail::in_expression_impl<Check::value, Expr, Lhs, Rhs...>::type;

}


#endif

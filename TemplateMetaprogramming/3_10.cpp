#include <ranges>
#include <concepts>


template<std::ranges::view R>	//. ranges::view concept
class custom_take_view
	: public std::ranges::view_interface<custom_take_view<R>>
{
	R m_base{};
	std::ranges::range_difference_t<R> m_count{};

public:
	custom_take_view() = default;

	constexpr custom_take_view(R base, std::ranges::range_difference_t<R> count) : m_base{ std::move(base) }, m_count{ count } {}

	constexpr R base() const& { return m_base; }
	constexpr R base() && {
		return  std::move(m_base);
	}


	constexpr auto begin() { return std::ranges::begin(m_base); }
	constexpr auto end() { return std::ranges::next(std::ranges::begin(m_base) + m_count); }

};

template<std::ranges::range R>
custom_take_view(R&& base, std::ranges::range_difference_t<R>)
->custom_take_view<std::ranges::views::all_t<R>>;


namespace details
{
	template<std::integral T>
	struct custom_take_range_adaptor_closure
	{
		T m_count;
		constexpr custom_take_range_adaptor_closure(T count) : m_count(count) {}

		template<std::ranges::viewable_range R>
		constexpr auto operator()(R&& r) const
		{
			return custom_take_view(std::forward<R>(r), m_count);
		}
	};


	struct custom_take_range_adaptor
	{
		template<typename ...Args>
		constexpr auto operator()(Args&&...args)
		{
			if constexpr (sizeof...(Args) == 1)
			{
				return custom_take_range_adaptor_closure{ args... };
			}
			else
			{
				return custom_take_view(std::forward<Args>(args)...);
			}
		}
	};

	template<std::ranges::viewable_range R, typename T>
	constexpr auto operator|(R&& r, const custom_take_range_adaptor_closure<T>& a)
	{
		return a(std::forward<R>(r));
	}

}

template<std::ranges::viewable_range R, std::invocable<R> Adaptor>
constexpr auto operator|(R&& r, const Adaptor& a)
{
	return a(std::forward<R>(r));
}


namespace views
{
	inline details::custom_take_range_adaptor custom_take;
}


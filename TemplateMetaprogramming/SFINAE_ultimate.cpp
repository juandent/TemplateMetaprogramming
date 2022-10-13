#include <type_traits>


template<typename Lambda> struct is_valid_helper
{
	template<typename...LambdaArgs>
	constexpr auto test(int) -> decltype(std::declval<Lambda>()(std::declval<LambdaArgs>()...), std::true_type())
	{
		return std::true_type();
	}
	template<typename...LambdaArgs>
	constexpr auto test(...) -> std::false_type
	{
		return std::false_type();
	}
	template<typename...LambdaArgs>
	constexpr auto operator()(const LambdaArgs& ...)
	{
		return this->test<LambdaArgs...>(0);
	}
};

template<typename Lambda>
constexpr auto is_valid(const Lambda&)
{
	return is_valid_helper<Lambda>();
}


auto is_addable = is_valid([](auto&& x) -> decltype(x + x) {});
auto is_multi_addable = is_valid([](auto&& x, auto&& y) -> decltype(x + y) {});

struct Sample
{
	int x = 0;
	int operator+(int y)
	{
		return x + y;
	}
};

Sample same;
constexpr bool is = is_addable(same);
int some;
double other;
constexpr bool is_m = is_multi_addable(same, some);

void useIsValid()
{
	auto res = same + 5;
}


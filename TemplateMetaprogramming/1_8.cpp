


#include <type_traits>
#include <concepts>
#include <xutility>

template<typename T, typename...Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

template<typename T, typename...>
struct first_arg
{
	using type = T;
};

template<typename...Args>
using first_arg_t = typename first_arg<Args...>::type;


template<typename...Args>
concept Addable = requires(Args...args)
{
	(... + args);
		requires are_same_v<Args...>;
		requires sizeof...(Args) > 1;
	{(... + args) } noexcept -> std::convertible_to<first_arg_t<Args...>>; //     std::same_as<std::add_lvalue_reference_t<first_arg_t<Args...>>>;
};


template<typename...Args>
	requires Addable<Args...>
auto Add(Args&& ...args)
{
	return (... + args);
}


template<bool nexcept, bool operatorPlus, bool validReturnType>
struct Stub
{

	Stub& operator+(const Stub&  rhs) noexcept(nexcept) requires (operatorPlus && validReturnType)
	{
		return *this;
	}

	int operator+(const Stub& rhs) noexcept(nexcept) requires (operatorPlus && not validReturnType)
	{
		return {};
	}
};

using NoAdd = Stub<true, false, true>;
using ValidClass = Stub<true, true, true>;
using NotNoexcept = Stub<false, true, true>;
using DifferentReturnType = Stub<true, true, false>;


template<typename...Args>
concept Addable2 = requires(Args&&...args)
{
	{(... + args)} noexcept -> std::convertible_to<first_arg_t<Args...>>;  //std::same_as<std::add_lvalue_reference_t<first_arg_t<Args...>>>;
};

template<typename...Args> requires Addable2<Args...>
auto Add2(Args&& ...args)
{
	return (... + args);
}


static_assert(not Addable<int, double>);
static_assert(not Addable<int>);
static_assert(Addable<int, int>);
static_assert(Addable<ValidClass, ValidClass>);
static_assert(not Addable<NoAdd, NoAdd>);
static_assert(not Addable < NotNoexcept, NotNoexcept>);
static_assert(not Addable<DifferentReturnType, DifferentReturnType>);

#include <limits>

namespace _1_8
{
	void use()
	{
		Stub<true, true, true> s, t;
		auto v = s + t;

		constexpr bool same = std::same_as<int, int&>;

		using ty = first_arg_t<int, bool>;

		constexpr double val = 10e307;
		constexpr double value = 0x10p4;


		constexpr double max = std::numeric_limits<double>::max_exponent10;

		auto res = Add2(1.55, 2, 3, 4, 5);

	}
}

#include <concepts>
#include <iterator>
#include <xutility>

template<typename I>
concept random_iterator = requires(I i, I j, std::iter_difference_t<I> n)
{
	{i+=n}->std::same_as<I&>;
	{j+ n}->std::same_as<I>;
	{n+ j}->std::same_as<I>;
	{i-=n}->std::same_as<I&>;
	{j-n}->std::same_as<I>;
	{j[n]}->std::same_as<std::iter_reference_t<I>>;
};

#include <concepts>
#include <type_traits>
#include <algorithm>
#include <optional>
#include <vector>
#include <list>
#include <iostream>


template<typename T, typename ...>
struct first_arg
{
	using type = T;
};

template<typename ...Args>
using first_arg_t = typename first_arg<Args...>::type;

template<typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;

template<typename T, typename...Args>
constexpr bool are_same_v = std::conjunction<is_same_v<T, Args>...>::value;

template <typename T, typename...>
struct all_same_type;

template <typename T>
struct all_same_type<T>
{
	static constexpr bool value = true;
};
template <typename T, typename U, typename... Us>
struct all_same_type<T, U, Us...>
{
	static constexpr bool value =
		std::is_same<T, U>::value && all_same_type<T, Us...>::value;
};



// using C++17
template<typename...Args>
std::enable_if_t<are_same_v<Args...>, first_arg_t<Args...>>
add( const Args&...args) noexcept
{
	return (args + ...);
}


// using C++14
#if 1
template<typename T>
T add14(const T& t)
{
	return t;
}

template<typename T, typename...Tail, typename = std::enable_if_t<all_same_type<T,Tail...>::value, first_arg_t<T,Tail...>>>
std::enable_if_t<all_same_type<T, Tail...>::value, first_arg_t<T, Tail...>>
add14( const T& t, const Tail& ... tail)
{
	return t + add14(tail...);
}

#else

template <typename T> constexpr T add14(T const& x) { return x; }

template <typename T, typename... Ts, typename = std::enable_if_t<all_same_type<T, Ts...>::value>>
	constexpr T add14(T const& x, Ts const&... xs) {
	return x + add14(xs...);
}

#endif
// template<typename T, typename U, typename...Tail>
// std::enable_if<are_same_v<T, U, Tail...>, first_arg_t<T, U, Tail...>>::type
// add14(const T& t, const U& u, const Tail& ... tail)
// {
// 	return t + add14(u, tail...);
// }




// simple requirements (SR)
template<typename ...Args>
requires all_same_type<Args...>::value
auto AddSR(Args&& ... args) noexcept
{
	return (... + args);
}

template<typename ...Args>
concept addable1 = requires (Args...args)
{
	(... + args);
};

// Nested requirements
template<typename ...Args>
concept addable2 = requires (Args...args)
{
	(... + args);
		requires are_same_v<Args...>;
		requires sizeof...(Args) > 1;
};

// compound requirements
template<typename ...Args>
concept addable3 = requires (Args...args)
{
	(... + args);
		requires are_same_v<Args...>;
		requires sizeof...(Args) > 1;
	{ (... + args) } noexcept ->  std::convertible_to<all_same_type<first_arg_t<Args...>>>;
};


//type requirement
template<typename T>
concept containerTypes = requires (T t)
{
	typename T::value_type;
	typename T::size_type;
	typename T::allocator_type;
	typename T::iterator;
	typename T::const_iterator;
};

template<typename Cont>
requires containerTypes<Cont>
auto max_value(Cont&& cont) -> std::remove_cvref_t<decltype(cont)>::value_type
{
	typename std::remove_cvref_t<decltype(cont)>::value_type * pp;
	auto x = std::max_element(cont.begin(), cont.end());
	return *x;
}

template<typename Cont>
	requires containerTypes<Cont>
auto max_value(Cont& cont) -> std::remove_cvref_t<decltype(cont)>::value_type
{
	typename std::remove_cvref_t<decltype(cont)>::value_type* pp;
	auto x = std::max_element(cont.begin(), cont.end());
	return *x;
}

// compiler error jdh reported may 2, 2022
std::integral auto max_value_2(containerTypes auto& cont)    //-> std::remove_cvref_t<decltype(cont)>::value_type
{
	typename std::remove_cvref_t<decltype(cont)>::value_type* pp;
	auto x = std::max_element(cont.begin(), cont.end());
	return *x;
}


void useAdd()
{
	auto x = add14(5, 20, 35, 10);
	
	auto y = AddSR(15, 25);

	std::vector v{ 10,20,30,50 };

	typename decltype(v)::value_type p = *std::max_element(v.begin(), v.end());

	auto m = max_value(v);

	auto mmm = max_value(std::vector<int>{15, 22, 33});

	const std::integral auto mmmm = max_value_2(v);

	std::optional<int> opt;

}


// whether a certain statement is valid




// nested requirements (NR)
// compound requirements (CR)
// type requirements (TR)


// Conditional methods 1.12

template<typename T>
class my_optional
{
public:
	my_optional() = default;

	~my_optional() requires (not std::is_trivially_destructible_v<T>)
	{
		std::cout << "~ not trivially destructible" << std::endl;
		if (has_value())	// pending: do something
			;
	}

	~my_optional() requires (std::is_trivially_destructible_v<T>) = default;

	my_optional(const my_optional& other) requires                                                                                                                                                                                                                                                                                                                                                                                                                     std::is_copy_constructible_v<T>
	{
		value = other.value;
	}


private:
	bool value = false;
	bool has_value() { return value; }	// obviously a stub
};

class NotTriviallyDestructible
{
public:

	~NotTriviallyDestructible()
	{
		// dummy but not trivial
		for(int i=0; i<1000; ++i)
		{
			;	
		}
	}

	NotTriviallyDestructible(const NotTriviallyDestructible&) = default;
};

void useMyOptional()
{
	my_optional<int> opt;

	my_optional<NotTriviallyDestructible> opt2;
	my_optional<NotTriviallyDestructible> opt3{ opt2 };

	constexpr  bool a = false;
	constexpr  bool b = true;
	constexpr  bool c = a and (a or b);


}


template<typename T>
concept HasSortMethod = requires (T t)
{
	t.sort();
};

template<typename T>
concept HasClearMethod = requires (T t)
{
	t.clear();
};

template<typename T>
concept HasBothMethods = HasSortMethod<T> and HasClearMethod<T>;

template<HasBothMethods T>
void PrintSorted(T c)
{
	c.sort();

	for( const auto& e : c)
	{
		std::cout << e << " ";
	}
	std::cout << "\n";
}

void sortedList()
{
	std::list<int> l{ 12,24,67, 1 };
	std::vector v{ 15,33,1,4 };

	PrintSorted(l);
	// PrintSorted(v);

}
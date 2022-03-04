#include "stdafx.h"


template<typename T>
struct is_vector
{
	constexpr static bool value = false;
};

template<typename T>
struct is_vector<std::vector<T>>
{
	constexpr static bool value = true;
};

template<typename Iterator>
struct value_type
{
	using type = typename std::iterator_traits<Iterator>::value_type;	// the value type of the Iterator
	static constexpr bool is_container = is_vector<type>::value;		// whether the value type is a vector
};

template<typename container>
struct nested_iterators
{
	using inner_iterator = typename container::iterator;
	using inner_value = typename std::iterator_traits<inner_iterator>::value_type;
};


template<typename Iterator>   requires (std::is_arithmetic<typename value_type<Iterator>::type>::value)
typename std::iterator_traits<Iterator>::value_type
sum(Iterator start, Iterator end);


template<typename Iterator>   requires (value_type<Iterator>::is_container)
// typename nested_iterators<typename value_type<Iterator>::type>::inner_value
auto
sum(Iterator start, Iterator end)
{
	constexpr bool is = value_type<Iterator>::is_container;
	static_assert(is);
	using container = value_type<Iterator>::type;
	typename nested_iterators<container>::inner_value x{ 0 };
	for (; start != end; ++start)
	{
		auto it = start->begin();
		x += sum(start->begin(), start->end());
	}
	return x;
}


template<typename Iterator>   requires (std::is_arithmetic<typename value_type<Iterator>::type>::value)
typename std::iterator_traits<Iterator>::value_type
sum(Iterator start, Iterator end)
{
	constexpr bool is = value_type<Iterator>::is_container;
	static_assert(!is);
	typename std::iterator_traits<Iterator>::value_type x{ 0 };

	for (; start != end; ++start)
	{
		x += *start;
	}
	return x;
}


void useSumVectorOfVectors()
{
	std::vector<std::vector<int>> vec{ {1,2,3},{5,6,7},{9,10,11} };
	// std::vector<int> vec;

	constexpr bool is = value_type<decltype(vec.begin())>::is_container;
	using value_t = value_type<decltype(vec.begin())>::type;

	nested_iterators<value_t>::inner_value x;

	auto ret = sum(vec.begin(), vec.end());

	constexpr bool is_v = is_vector<decltype(vec)>::value;

	using vii = std::vector<int>::iterator;
	using vvi = std::vector<std::vector<int>>::iterator;
}

void useSum()
{
	std::vector<int> vec{ 1,2,3,4 };
	auto ret = sum(vec.begin(), vec.end());
	std::vector<std::string> vecs{ "hello", "mother" };
	// auto r = sum(vecs.begin(), vecs.end());      // FAILS, non arithmetic

}

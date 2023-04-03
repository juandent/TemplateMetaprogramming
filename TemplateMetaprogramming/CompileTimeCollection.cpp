#include <iostream>
#include <type_traits>
#include <memory>


// type collection
template<typename...T>
struct Collection
{
	using type = Collection<T...>;
};

// data collection
template<auto ... Args>
struct ValueCollection
{
	using type = ValueCollection<Args...>;
};


// length
template<typename TCont>
struct Length;

template<template <typename ...> class Container, typename Head, typename...Tail>
struct Length<Container<Head, Tail...>>
{
	static constexpr size_t value = 1 + Length<Container<Tail...>>::value;
};

template<template <typename ...> class Container, typename Head>
struct Length<Container<Head>>
{
	static constexpr size_t value = 1;
};

template<template<typename...> class Container>
struct Length<Container<>>
{
	static constexpr size_t value = 0;
};

// append
template<typename TCont, typename New>
struct Append;



template<template <typename ...> class Container, typename New, typename...  Elements>
struct Append<Container<Elements...>, New>
{
	using type = Container < Elements..., New>;
};

// value append
template<typename TCont, auto New>
struct ValueAppend;


template<template <auto ...Args> class Container, auto New, auto ... Elements>
struct ValueAppend<Container<Elements... >, New>
{
	using type = Container < Elements..., New>;
};



// prepend
template<typename TCont, typename New>
struct Prepend;

template<template<typename ...> class Container, typename New, typename... Elements>
struct Prepend<Container<Elements...>, New>
{
	using type = Container<New, Elements...>;
};


// search return position
namespace detail
{
	template<typename TCont, typename TFind, size_t Last, size_t Pos>
	struct Search;


	template<template<typename ...> class Container, typename TFind, size_t Last, typename Head, typename...Tail>
	struct Search<Container<Head, Tail...>, TFind, Last, Last>
	{
		static constexpr size_t pos = std::is_same_v<TFind, Head> ? Last : Last + 1;
	};


	template<template<typename ...> class Container, typename TFind, size_t Pos, size_t Last, typename Head, typename...Tail>
	struct Search<Container<Head, Tail...>, TFind, Last, Pos>
	{
		static constexpr size_t pos = std::is_same_v<TFind, Head> ? Pos : Search<Container<Tail...>, TFind, Last, Pos + 1>::pos;
	};
}

template<typename TCont, typename TFind>
struct Search;


template<template<typename ...> class Container, typename TFind>
struct Search<Container<>, TFind>
{
	static constexpr size_t pos = -1;
};



template<template<typename ...> class Container, typename TFind, typename Head, typename...Tail>
struct Search<Container<Head, Tail...>, TFind>
{
	static constexpr size_t pos = detail::Search<Container<Head, Tail...>, TFind, sizeof...(Tail), 0>::pos;
};

namespace intermediate
{
	template<typename TVal, size_t N, size_t M, typename TProcessedTypes, typename ...TRemainTypes>
	struct ReplaceType_;

	template<typename TVal, size_t N,// TVal finally finds its place replacing TCurType!
		template<typename...> class TCont,
		typename ...TModifiedTypes,
		typename TCurType,
		typename ...TRemainTypes>
	struct ReplaceType_<TVal, N, N, TCont<TModifiedTypes...>, TCurType, TRemainTypes...>
	{
		using type = TCont<TModifiedTypes..., TVal, TRemainTypes...>;
	};


	template<typename TVal, size_t N, size_t M,// 
		template<typename...> class TCont,// container class
		typename ...TModifiedTypes,// first call comes empty
		typename TCurType,// head of types -- types must be split to move head into container
		typename ...TRemainTypes>// tail of types
	struct ReplaceType_<TVal, N, M, TCont<TModifiedTypes...>, TCurType, TRemainTypes...>
	{
		using type = typename ReplaceType_<TVal, N, M + 1, TCont<TModifiedTypes..., TCurType>, TRemainTypes...>::type;
	};


	// carry rawVal until N==M, then insert replacing TCurType
	// using new_type = NewTupleType<rawVal, TagPos, Values<>, TTypes...>;// type of parameter received, position of Tag in TParameters, empty container, types associated with container

	template<typename TVal, size_t TagPos, typename TCont, typename...TRemainTypes>
	using ReplaceType = typename ReplaceType_<TVal, TagPos, 0, TCont, TRemainTypes...>::type;
}

namespace FromCollection
{

	template<typename TVal, size_t N, size_t M, typename TProcessedTypes, typename TResultTypes>
	struct ReplaceType_;

	template<typename TVal, size_t N,// TVal finally finds its place replacing TCurType!
		template<typename...> class TCont,
		typename ...TModifiedTypes,
		typename TCurType,
		typename ...TRemainTypes,
		template<typename...> class TResult> // new container class
	struct ReplaceType_<TVal, N, N, TCont<TCurType, TRemainTypes...>, TResult<TModifiedTypes... >>
	{
		using type = TResult<TModifiedTypes..., TVal, TRemainTypes...>;
	};


	template<typename TVal, size_t N, size_t M,// 
		template<typename...> class TCont,// container class
		typename ...TModifiedTypes,// first call comes empty
		typename TCurType,// head of types -- types must be split to move head into container
		typename ...TRemainTypes, // tail of types
		template<typename...> class TResult> // new container class
	struct ReplaceType_<TVal, N, M, TCont<TCurType, TRemainTypes...>, TResult<TModifiedTypes... >>
	{
		using type = typename ReplaceType_<TVal, N, M + 1, TCont<TRemainTypes...>, TResult<TModifiedTypes..., TCurType>>::type;
	};


	// carry rawVal until N==M, then insert replacing TCurType
	// using new_type = NewTupleType<rawVal, TagPos, Values<>, TTypes...>;// type of parameter received, position of Tag in TParameters, empty container, types associated with container

	template<typename TVal, size_t TagPos, typename TCont>
	using ReplaceType = typename ReplaceType_<TVal, TagPos, 0, TCont, Collection<>>::type;


	// InsertType
	template<typename TVal, size_t N, size_t M, typename TProcessedTypes, typename TResultTypes>
	struct InsertType_;

	template<typename TVal, size_t N,// TVal finally finds its place replacing TCurType!
		template<typename...> class TCont,
		typename ...TModifiedTypes,
		typename TCurType,
		typename ...TRemainTypes,
		template<typename...> class TResult> // new container class
	struct InsertType_<TVal, N, N, TCont<TCurType, TRemainTypes...>, TResult<TModifiedTypes... >>
	{
		using type = TResult<TModifiedTypes..., TVal, TCurType, TRemainTypes...>;
	};


	template<typename TVal, size_t N, size_t M,// 
		template<typename...> class TCont,// container class
		typename ...TModifiedTypes,// first call comes empty
		typename TCurType,// head of types -- types must be split to move head into container
		typename ...TRemainTypes, // tail of types
		template<typename...> class TResult> // new container class
	struct InsertType_<TVal, N, M, TCont<TCurType, TRemainTypes...>, TResult<TModifiedTypes... >>
	{
		using type = typename InsertType_<TVal, N, M + 1, TCont<TRemainTypes...>, TResult<TModifiedTypes..., TCurType>>::type;
	};

	template<typename TVal, size_t TagPos, typename TCont>
	using InsertType = typename InsertType_<TVal, TagPos, 0, TCont, Collection<>>::type;


	// TagPos
	template<typename Tag, size_t P, size_t N, typename Container>
	struct TagPosHelper;

	template<typename Tag, size_t N, typename Container>
	struct TagPosHelper<Tag, N, N, Container>
	{
		constexpr static size_t Pos = N;
	};

	template <typename Tag,	size_t P, size_t N, typename Head, typename ...Elements, template<typename...> class Cont>
	struct TagPosHelper<Tag, P, N, Cont<Head, Elements...>>
	{
		constexpr static size_t Pos = std::is_same_v<Tag, Head> ? P : TagPosHelper<Tag, P + 1, N, Cont<Elements...>>::Pos;
	};

	template<typename Tag, typename Container>
	struct TagPos;

	template<typename Tag, typename ...Elements, template<typename...> class Cont>
	struct TagPos<Tag, Cont<Elements...>>
	{
		constexpr static size_t Pos = TagPosHelper<Tag, 0, sizeof...(Elements), Cont<Elements...>>::Pos;
	};

	struct A;
	struct B;
	struct C;
	struct D;

	void useTagPos()
	{
		using cont = Collection<A, B, C>;
		constexpr size_t pos = TagPos<D, cont>::Pos;
	}
}

#include <chrono>
#include <iostream>

/**
 * \brief 
 */

using FromCollection::ReplaceType;
using FromCollection::InsertType;

void useCollection()
{
//#define RUN
#define CONSTINIT

	const auto start = std::chrono::high_resolution_clock::now();

#ifdef RUN
	using cont =  Collection<int, double, char>;

	constexpr size_t length = Length<cont>::value;

	using cont_extra = Append<cont, long long>::type;

	using cont_prepend = Prepend<cont, long long>::type;

	constexpr size_t ppos = Search<cont, char>::pos;

	constexpr size_t pppos = Search<Collection<>, char>::pos;
	static_assert(pppos == -1);

	using tt = ReplaceType<char*, 2, cont>::type;

	using rr = InsertType<char*, 1, cont>::type;

	using rrr = InsertType<char*, 0, cont>::type;

	using rrrr = InsertType<char*, 2, cont>::type;

#endif
#ifdef CONSTINIT
	using cont = Collection<int, double, char>;

	constinit static size_t length = Length<cont>::value;

	using cont_extra = Append<cont, long long>::type;

	using cont_prepend = Prepend<cont, long long>::type;

	constinit static size_t ppos = Search<cont, char>::pos;

	constinit  const static size_t pppos = Search<Collection<>, char>::pos;
	static_assert(pppos == -1);

	using tt = ReplaceType<char*, 2, cont>::type;

	using rr = InsertType<char*, 1, cont>::type;

	using rrr = InsertType<char*, 0, cont>::type;

	using rrrr = InsertType<char*, 2, cont>::type;

#endif
#ifdef NO_ASSIGNMENT
	using cont = Collection<int, double, char>;

	Length<cont>::value;

	Append<cont, long long>::type;

	Prepend<cont, long long>::type;


	Search<cont, char>::pos;

	Search<Collection<>, char>::pos;
	//static_assert(pppos == -1);

	using tt = ReplaceType<char*, 2, cont>::type;

	using rr = InsertType<char*, 1, cont>::type;

	using rrr = InsertType<char*, 0, cont>::type;

	using rrrr = InsertType<char*, 2, cont>::type;

#endif

	const auto stop = std::chrono::high_resolution_clock::now();

	auto lapse = stop - start;

	std::cout << lapse << std::endl;

	using coll = ValueCollection< 1, 3, 6, 9>;
	using coll__ = ValueAppend<coll, 15>::type;


}


template<unsigned long long T>
struct Fibonacci
{
	constexpr static unsigned long long value = (Fibonacci<T - 1>::value + Fibonacci<T - 2>::value);
};

template<>
struct Fibonacci<0>
{
	constexpr static unsigned long long value = 1;
};

template<>
struct Fibonacci<1>
{
	constexpr static unsigned long long value = 1;
};

template<>
struct Fibonacci<2>
{
	constexpr static unsigned long long value = 1;
};

void useFibonacci()
{
	const auto start = std::chrono::high_resolution_clock::now();
	constexpr auto x = Fibonacci<450>::value;
	const auto stop = std::chrono::high_resolution_clock::now();
	auto lapse = stop - start;
	std::cout << x << std::endl;
	std::cout << lapse << std::endl;
}

// Metafunction Twice
template<auto T> requires std::is_arithmetic_v<decltype(T)>
struct Twice
{
	constexpr static auto value = T * 2;
};

template<auto T> requires std::is_arithmetic_v<decltype(T)>
struct Thrice
{
	constexpr static auto value = T * 3;
};

// for loop
template<bool skip, int counter, int start, int stop, template<auto > class TFunc, typename TCont, typename TResult>
struct Execute_;


template<int counter, int start, int stop, template<auto > class TFunc, template<auto...> class TCont, auto Head, auto... Elements, template<auto...> class TResult, auto ... newElements>
struct Execute_<false, counter, start, stop, TFunc, TCont<Head, Elements...>, TResult<newElements...>>
{
	constexpr static auto transformed = TFunc<Head>::value;

	using type = typename Execute_<(counter  > start + 1), counter, start + 1, stop, TFunc, TCont<Elements...>, typename TResult<newElements..., transformed>::type >::type;
};

template<int counter, int start, int stop, template<auto > class TFunc, template<auto...> class TCont, auto Head, auto... Elements, template<auto...> class TResult, auto ... newElements>
struct Execute_<true, counter, start, stop, TFunc, TCont<Head, Elements...>, TResult<newElements...>>
{
	using type = typename Execute_<(counter  > start+1), counter, start + 1, stop, TFunc, TCont<Elements...>, typename TResult<newElements..., Head>::type >::type;
};

template<int counter, int stop, template<auto > class TFunc, template<auto...> class TCont, auto Head, auto... Elements, template<auto...> class TResult, auto ... newElements>
struct Execute_< false, counter, stop, stop, TFunc, TCont<Head, Elements...>, TResult<newElements...>>
{
	constexpr static auto transformed = TFunc<Head>::value;
	using type = TResult<newElements..., transformed, Elements...>;
};

template<int counter, int stop, template<auto > class TFunc, template<auto...> class TCont, auto Head, auto... Elements, template<auto...> class TResult, auto ... newElements>
struct Execute_< true, counter, stop, stop, TFunc, TCont<Head, Elements...>, TResult<newElements...>>
{
	using type = TResult<newElements..., Head, Elements...>;
};


template<int start, int stop, template<auto> class TFunc, typename Container>
using Execute = typename Execute_< (start > 0), start, 0, stop, TFunc, Container, ValueCollection<>>::type;


void useForLoop()
{
	constexpr auto v = Twice<3>::value;
	static_assert(v == 6);

	using cont = ValueCollection<1, 4, 9, 12, 13, 15>::type;
	using modifiedContainer = Execute<2, 4, Twice, cont>;
	static_assert(std::is_same_v<modifiedContainer, ValueCollection<1, 4, 18, 24, 26, 15>>);


	std::vector<int> vec{ 1, 4, 9, 12, 13, 15 };

	for( int i=2; i <= 5; ++i)
	{
		vec[i] *= 2;
	}



	using hetero = ValueCollection<2, 5.55, 7L>;
	using modifHetero = Execute<0, 2, Twice, hetero>;
	static_assert(std::is_same_v<modifHetero, ValueCollection<4, 11.1, 14L>>);
}



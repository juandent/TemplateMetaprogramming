#include <iostream>
#include <type_traits>
#include <memory>



template<typename...T>
struct Collection
{
	using type = Collection<T...>;
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

	// template<template<typename ...> class Container, typename TFind, size_t Last>
	// struct Search<Container<>, TFind, Last, Last>
	// {
	// 	static constexpr size_t pos = Last + 1;
	// };


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
}



/**
 * \brief 
 */
void useCollection()
{
	using cont =  Collection<int, double, char>;

	constexpr size_t length = Length<cont>::value;

	using cont_extra = Append<cont, long long>::type;

	using cont_prepend = Prepend<cont, long long>::type;


	constexpr size_t ppos = Search<cont, char>::pos;

	constexpr size_t pppos = Search<Collection<>, char>::pos;
	static_assert(pppos == -1);


	//using t = typename ReplaceType::NewTupleType_<unsigned short, 1, 0, Collection<>, unsigned char*, float>::type;

	using tt = typename FromCollection::ReplaceType<char*, 2, cont>::type;

	using rr = FromCollection::InsertType<char*, 1, cont>::type;

	using rrr = FromCollection::InsertType<char*, 0, cont>::type;

	using rrrr = FromCollection::InsertType<char*, 2, cont>::type;

}

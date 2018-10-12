#include <string>
#include <iostream>


struct Nil {};

template<typename HeadT, typename TailT = Nil>
struct Cons
{
	using Head = HeadT;
	using  Tail = TailT;
};

template<typename List>
struct IsEmpty
{
	static constexpr bool value = false;
};

template<>
struct IsEmpty<Nil>
{
	static constexpr bool value = true;
};

template<typename List,
	template<typename T, typename U> class Compare,
	bool = IsEmpty<List>::value>
	class InsertionSortT;



template<typename List>
struct PopFrontT
{
	using Type = typename List::Tail;
};

#ifdef NIL_ENABLE
  template<>
struct PopFrontT<Nil>
{
	using Type = Nil;
};
#endif



#if 0
  template<typename Head, template<typename T, typename U> class Compare>
struct PopFrontT<InsertionSortT<Cons<Head, Nil>, Compare, false>>
{
	using Type = Nil;
};
#endif


template<typename List>
using PopFront = typename PopFrontT<List>::Type;



template<typename List>
struct FrontT
{
	using Type = typename List::Head;
};

#ifdef NIL_ENABLE 
  template<>
struct FrontT<Nil>
{
	using Type = Nil;
	using Head = Nil;
};

template<typename Head>
struct FrontT<Cons<Head, Nil>>
{
	using Type = Head;
};
#endif





template<typename List>
using Front = typename FrontT<List>::Type;



template<typename List, typename Element, template<typename T, typename U> class Compare, bool isEmpty = IsEmpty<List>::value>
class InsertSortedT;


template<typename List, template<typename T, typename U> class Compare>
using InsertionSort = typename InsertionSortT<List, Compare>::Type;

// insert first element into sorted list
template<typename List, template<typename T, typename U> class Compare>
class InsertionSortT<List, Compare, false>
	: public InsertSortedT< typename InsertionSortT<PopFront<List>, Compare>::Type, Front<List>, Compare>
{
public:
//	using Type = typename InsertSortedT< typename InsertionSortT<PopFront<List>, Compare>::Type, Front<List>, Compare>::Type;
};


// basis case (empty list is sorted)
template<typename List, template<typename T, typename U> class Compare>
class InsertionSortT<List, Compare, true>
{
public:
	using Type = List;
};


template<bool cond, typename TrueType, typename FalseType>
struct IfThenElseT {
	using Type = TrueType;
};

template<typename TrueType, typename FalseType>
struct IfThenElseT<false, TrueType, FalseType> {
	using Type = FalseType;
};

template<bool cond, typename TrueType, typename FalseType>
using IfThenElse = typename IfThenElseT<cond, TrueType, FalseType>::Type;

template<typename List, typename Element>
struct PushFrontT
{
	using Type = Cons<Element, List>;
};

template<typename List, typename Element>
using PushFront = typename PushFrontT<List, Element>::Type;

// yield T when using member Type:
template<typename T>
struct IdentityT {
	using Type = T;
};

template<typename T>
using Identity = typename IdentityT<T>::Type;


// recursive case
template<typename List, typename Element, template<typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, false>
{
	using NewTail =  typename IfThenElseT< Compare<Element, Front<List>>::value, List,
		typename InsertSortedT<PopFront<List>, Element, Compare>::Type>::Type;

	using NewHead = IfThenElse< Compare<Element, Front<List>>::value, Element, Front<List>>;
public:
	using Type = PushFront< NewTail, NewHead>;
};


// basis case
template<typename List, typename Element, template<typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, true>
	: public PushFrontT<List, Element>
{
public:
	//using Head = Element;
	//using Tail = List;
};


template<typename List, typename Element, template<typename T, typename U> class Compare>
using InsertSorted = typename InsertSortedT<List, Element, Compare>::Type;


template<typename T, typename U>
struct SmallerThanT
{
	static constexpr bool value = sizeof(T) < sizeof(U);
};

void conslistester()
{
	//using SmallList = Cons<double>;
	using FrontElement = Front<Cons<double>>;

	using SmallList = Cons<double>;
	using SmallListSorted = typename InsertionSortT<SmallList, SmallerThanT>::Type;
	using Sorted = typename InsertSortedT<SmallList, long long, SmallerThanT, false>::Type;


	using ConsList = Cons<int, Cons<char, Cons<short, Cons<double>>>>;
	using SortedTypes = InsertionSort<ConsList, SmallerThanT>;


	using Sorted2 = typename InsertSorted<Cons<long long>, double,SmallerThanT>::Tail;
	using FrontOfSorted2 = typename Sorted2::Head;
	using Expected = Cons<char, Cons<short, Cons<int, Cons<double>>>>;
	std::cout << std::is_same<SortedTypes, Expected>::value << std::endl;

	using Popped = PopFront<ConsList>;
	using FrontConsList = Front<ConsList>;

}


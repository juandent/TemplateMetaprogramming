#include "stdafx.h"
#include <type_traits>

#include <boost\mpl\fold.hpp>
#include <boost\mpl\reverse_fold.hpp>
#include <boost\mpl\placeholders.hpp>
#include <boost\mpl\clear.hpp>
#include <boost\mpl\push_front.hpp>
#include <boost\mpl\vector.hpp>
#include <boost\mpl\equal.hpp>
#include <boost\type_traits\is_float.hpp>



namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;


// first as runtime code:

#include <deque>
#include <algorithm>

using sequence = std::deque<int>;


struct combine_back
{
	sequence operator()(sequence prev, int head)
	{
		sequence combined{ prev };
		combined.push_back(head);
		return combined;
	}
};

auto tail(sequence seq) -> sequence
{
	// skip the first element
	auto start = seq.begin();
	++start;
	sequence res{ start, seq.end() };
	return res;
}

auto head(const sequence& seq) -> int
{
	return seq[0];
}

void display(const std::string& title, const sequence& seq)
{
	std::cout << title << ": ";

	for (auto& elem : seq)
	{
		std::cout << elem << ", ";
	}
	std::cout << "\n";
}

template<typename BinaryOp>
auto fold(sequence seq, sequence prev, BinaryOp op) -> sequence
{
	display ( "seq", seq);
	display ( "prev", prev);

	if (seq.empty())
	{
		return prev;
	}
	else		// combine the first element with prev
	{		// and process the rest recursively

		return fold(tail(seq), op(prev, head(seq)), op);
	}
}


template<typename BinaryOp>
auto reverse_fold(sequence seq, sequence prev, BinaryOp op) -> sequence
{
	display("seq", seq);
	display("prev", prev);

	if (seq.empty())
	{
		return prev;
	}
	else
	{		// process the rest of the sequence
			// and combine it with the first element
		return op(
			reverse_fold(tail(seq), prev, op), head(seq));
	}
}


void doReverseAtRunTime()
{
	sequence v{ 1,2,3,4 };

	// initial type:
	sequence output{};

	//auto res = fold(v, output, combine_back{});
	auto reverse = reverse_fold(v, output, combine_back{});
}


template<typename Seq>
struct reverse : mpl::fold<
	Seq,
	typename mpl::clear<Seq>::type,		// initial type
	mpl::push_front<_,_>
>
{};


template<typename T>
struct Dummy {};

using seq = mpl::vector< int, double, long >;

using reverted = reverse<seq>::type;

constexpr bool equalToMe = mpl::equal<seq, seq>::value;

constexpr bool equal = mpl::equal<reverted, mpl::vector<long, double, int>>::value;




//////////////////////////////// fold sample from Boost's web page


using types = mpl::vector<long, float, short, double, float, long, long double>;

using number_of_floats = mpl::fold<
	types
	, mpl::int_<0>
	, mpl::if_< boost::is_float<_2>, mpl::next<_1>, _1 >
>::type;

static_assert(number_of_floats::value == 4, "");



namespace JD {
	namespace Functions
	{
		template<typename BinaryOp>
		auto fold(sequence seq, sequence prev, BinaryOp op) -> sequence
		{
			if (seq.empty())
			{
				return prev;
			}
			else		// combine the first element with prev
			{		// and process the rest recursively

				return fold(tail(seq), op(prev, head(seq)), op);
			}
		}
	}
}

////////////////////////////////////////////
// programming a meta fold:

namespace JD
{
	struct nil_t;

	template<size_t N, typename Head, typename...Tail>
	struct get_at
	{
		using type = typename get_at<N - 1, Tail...>::type;
	};

	template<typename Head, typename...Tail>
	struct get_at<0, Head, Tail...>
	{
		using type = Head;
	};

	// convenience alias template
	template<size_t N, typename...Elements>
	using get_at_t = typename get_at<N, Elements...>::type;


	template<typename...TypeElements>
	struct vector
	{
		template<size_t N>
		struct get_at
		{
			using type = get_at_t<N, TypeElements...>;
		};
		template<typename Elem>
		struct push_back
		{
			using type = vector<TypeElements..., Elem>;
		};
		template<typename Elem>
		struct push_front
		{
			using type = vector<Elem, TypeElements...>;
		};
	};

	template<>
	struct vector<>
	{
		template<size_t N>
		struct get_at
		{
			using type = nil_t;
		};
	private:
		template<typename Elem>
		struct push
		{
			using type = vector<Elem>;
		};
	public:
		template<typename Elem>
		struct push_back : push<Elem>
		{};
		template<typename Elem>
		struct push_front : push<Elem>
		{};
	};

	template<typename>
	struct something
	{
		using type = nil_t;
	};

	template<template<typename...> typename Seq, typename Head, typename...Tail>
	struct something<Seq<Head, Tail...>>
	{
		using type = Head;
	};

	using aVector = vector<int, char>;
	using head = something<aVector>::type;


#if 0
	template<typename Elem>
	struct push_back
	{
		template<typename Seq, typename...ExistingElements>
		struct apply
		{
			using type = vector<Elem, ExistingElements...>;
		};
	};

	template<typename Elem>
	struct push_back
	{
		template<typename...ExistingElements>
		struct apply<vector<ExistingElements...>>
		{
			using type = vector<Elem, ExistingElements...>;
		};
	};

	using MyVector = vector<int, unsigned, char>;

	using res = push_back<long double>::apply<MyVector>::type;


#endif



	// sample sequence:
	using SampleSeq = vector<long, float, short>;


#if 0
	template<size_t N, template<typename Head, typename...Tail> class Vec>
	struct get_at<N, SampleSeq
	{
		using type = get_at_t<N, Elements...>;
	};
#endif

	template<typename>
	struct head
	{
		using type = nil_t;
	};
	template<template<typename...> class Seq, typename First, typename ...Rest>
	struct head<Seq<First,Rest...>>
	{
		using type = First;			// return type: an element of the seq
	};

	template<typename Seq>
	using head_t = typename head<Seq>::type;

	template<typename>
	struct tail
	{
		using type = nil_t;
	};
	template<template<typename...> class Seq, typename First, typename ...Rest>
	struct tail<Seq<First, Rest...>>
	{
		using type = Seq<Rest...>;	// return type: a sequence skipping the head element
	};
	template<typename Seq>
	using tail_t = typename tail<Seq>::type;


	// general template (primary template)
	template<typename Seq, typename Prev, typename BinaryOp>
	struct fold
	{
		using type = typename fold<tail_t<Seq>, typename BinaryOp::template apply<Prev, head_t<Seq>>::type,
			BinaryOp>::type;
	};
	// specialized template (end of recursion)
	template<typename Prev, typename BinaryOp>
	struct fold<nil_t, Prev, BinaryOp>
	{
		using type = Prev;
	};

	// fold_t: convenience template alias
	template<typename Seq, typename Prev, typename BinaryOp>
	using fold_t = typename fold<Seq, Prev, BinaryOp>::type;

	template<int I> 
	using int_ = std::integral_constant<int, I>;

	template<typename N>
	using succ = int_<N::value + 1>;

	// BinaryOp sample:
	struct accumulate_if_float
	{
		template<typename Sum, typename T>
		struct apply
		{
			using type = typename std::conditional<std::is_floating_point<T>::value, succ<Sum>, Sum>::type;
		};
	};

	template<typename Seq>
	constexpr auto number_of_floats_v = fold_t<Seq, int_<0>, accumulate_if_float>::value;

	// sample sequence:
	using MySeq = vector<long, float, short, double, float, long, long double>;

	static_assert(number_of_floats_v<MySeq> == 4, "there must be 4 floating points in this sequence");

	using grown_back = MySeq::push_back<char>::type;

	using elem_1 = grown_back::get_at<1>::type;

	constexpr bool eq = std::is_same<elem_1, float>::value;

	using grown_front = MySeq::push_front<char>::type;

	using elem0 = get_at_t<1, char, long>;


	// BinaryOp sample#2: (primary template)
	struct meta_push_back
	{
		template <typename State, typename Elem>
		struct apply
		{
			using type = typename State::template push_back<Elem>::type;
		};
	};


	using one_elem = vector<>::push_back<long>::type;

	using intelem = meta_push_back::apply<vector<float, int>, char>::type;

	using result = fold_t<MySeq, vector<>, meta_push_back>;

	using one = result::get_at<1>::type;


	//constexpr bool same_contents = mpl::equal(grown, vector<char, long, float, short, double, float, long, long double>)::value;

	// recursion stop:
	//template<typename Prev, typename BinaryOp>
	//struct fold<vector<>, Prev, BinaryOp>
	//{

	//};



}
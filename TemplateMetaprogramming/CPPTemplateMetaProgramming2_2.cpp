
#include <iostream>
#include <list>
#include <type_traits>
#include <memory>
#include <map>
#include <ostream>
#include <vector>
#include <concepts>

#if 0
std::integral
disjunction

template<template-parameter-list>
concept concept-name = constraint-expression;
#endif


namespace {

	struct NullParameter;


	namespace testing
	{
		template<typename Tag, size_t P, size_t N, typename ... T>
		struct Tag2PosTHelper;


		template<typename Tag, size_t N>
		struct Tag2PosTHelper<Tag, N, N>
		{
			constexpr static size_t Pos = N;
		};


		template<typename Tag, size_t P, size_t N, typename Head, typename... Tail>
		struct Tag2PosTHelper<Tag, P, N, Head, Tail...>
		{
			constexpr static size_t Pos = std::is_same_v<Tag, Head>  ? P : Tag2PosTHelper<Tag, P + 1, N, Tail...>::Pos;
		};

		template<typename Tag, typename...T>
		struct Tag2PosT
		{
			constexpr static size_t Pos = Tag2PosTHelper<Tag, 0, sizeof...(T), T...>::Pos;
		};
		struct A;
		struct B;
		struct C;
		struct D;

		void use()
		{
			constexpr size_t pos = Tag2PosT<D, A, B, C >::Pos;
		}

		template <typename  ...T>
		struct Container
		{
			std::tuple<T...> elements;
		};

		// size, container, elements
		template<size_t N, typename Element, template <typename...> class TCont, typename ...T>
		struct Fill
		{
			using type = typename Fill<N - 1, Element, TCont, Element, T...>::type;
		};
		// anchor N==>0
		template<typename Element, template<typename...> class TCont, typename ...T>
		struct Fill<0, Element, TCont, T...>
		{
			using type = TCont<T...>;
		};

		void fillContainer()
		{
			using filled = Fill<4, double, Container>::type;
			constexpr bool same = std::is_same_v<filled, Container<double, double, double, double>>;

			filled p;
			auto x = std::get<0>(p.elements);
		}

	}


	template<size_t Pos, typename Head, typename...Tail>
	struct GetType
	{
		using type = typename GetType<Pos - 1, Tail...>::type;
	};

	template<typename Head, typename...Tail>
	struct GetType<0, Head, Tail...>
	{
		using type = Head;
	};

	void getTypePorPosicion()
	{
		using type = GetType<2, int, long, char, double>::type;
	}

	template<size_t N, template<typename ...> class TCont, typename...T>
	struct Create_
	{
		using type = typename Create_<N - 1, TCont, NullParameter, T...>::type;
	};

	template<template<typename ...> class TCont, typename...T>
	struct Create_<0, TCont, T...>
	{
		using type = TCont<T...>;
	};

	template<typename TVal, size_t N, size_t M, typename TProcessedTypes, typename ...TRemainTypes>
	struct NewTupleType_;



	template<typename TVal, size_t N, size_t M,			// 
		template<typename...> class TCont,				// container class
		typename ...TModifiedTypes,						// first call comes empty
		typename TCurType,								// head of types -- types must be split to move head into container
		typename ...TRemainTypes>						// tail of types
	struct NewTupleType_<TVal, N, M, TCont<TModifiedTypes...>, TCurType, TRemainTypes...>
	{
		using type = typename NewTupleType_<TVal, N, M + 1, TCont<TModifiedTypes..., TCurType>, TRemainTypes...>::type;
	};

	template<typename TVal, size_t N,					// TVal finally finds its place replacing TCurType!
		template<typename...> class TCont,
		typename ...TModifiedTypes,
		typename TCurType,
		typename ...TRemainTypes>
	struct NewTupleType_<TVal, N, N, TCont<TModifiedTypes...>, TCurType, TRemainTypes...>
	{
		using type = TCont<TModifiedTypes..., TVal, TRemainTypes...>;
	};

	// carry rawVal until N==M, then insert replacing TCurType
	// using new_type = NewTupleType<rawVal, TagPos, Values<>, TTypes...>;	// type of parameter received, position of Tag in TParameters, empty container, types associated with container

	template<typename TVal, size_t TagPos, typename TCont, typename...TRemainTypes>
	using NewTupleType = typename NewTupleType_<TVal, TagPos, 0, TCont, TRemainTypes...>::type;

	template <typename Tag, typename Head, typename... Tail>
	constexpr size_t Tag2Pos()
	{
		if constexpr (sizeof...(Tail))
			return std::is_same_v<Tag, Head> ? 0 : 1 + Tag2Pos<Tag, Tail...>();
		else
			return std::is_same_v<Tag, Head> ? 0 : 1;
	}


	template<typename ...TParameters>
	struct VarTypeDict
	{
		template<typename...TTypes>
		struct Values
		{
			Values() = default;

			Values(std::shared_ptr<void>(&& input)[sizeof...(TTypes)])
			{
				for (size_t i = 0; i < sizeof...(TTypes); ++i)
				{
					m_tuple[i] = std::move(input[i]);
				}
				// for debugging:
				using type0 = typename GetType<0, TTypes...>::type;
				type0* p0;
				using type1 = typename GetType<1, TTypes...>::type;
				type1* p1;
				using type2 = typename GetType<2, TTypes...>::type;
				type2* p2;
			}


			template<typename TTag, typename TVal>
			auto Set(TVal&& val)  &&
			{
				constexpr static size_t TagPos = Tag2Pos<TTag, TParameters...>();

				using rawVal = std::decay_t<TVal>;
				rawVal* tmp = new rawVal{ std::forward<TVal>(val) };
				m_tuple[TagPos] = std::shared_ptr<void>(tmp, [](void* ptr)
					{
						rawVal* nptr = static_cast<rawVal*>(ptr);
						delete nptr;
					});
				using new_type = NewTupleType<rawVal, TagPos, Values<>, TTypes...>;	// type of parameter received, position of Tag in TParameters, empty container, types associated with container
				return new_type{ std::move(m_tuple) };

			}

			template<typename TTag>
			const auto& Get() const
			{
				constexpr static size_t TagPos = Tag2Pos<TTag, TParameters...>();
				using type = typename GetType<TagPos, TTypes...>::type;
				auto r = m_tuple[TagPos];
				return *(type*)r.get();
			}
		private:
			std::shared_ptr<void>   m_tuple[sizeof...(TTypes)];
		};

	public:
		static auto Create()
		{
			using type = typename Create_<sizeof...(TParameters), Values>::type;
			return type{};
		}
	};



	struct A;
	struct B;
	struct C;
	struct D;

}


namespace decay_samples
{

	void accept(int a[])
	{
		a[0];
	}
	void accept(int(&f)())
	{
		f();
	}

	template <class _Ty>
	constexpr _Ty&& forward_mine(std::remove_reference_t<_Ty>& _Arg) noexcept { // forward an lvalue as either an lvalue or an rvalue
		_Ty& ret = static_cast<_Ty&&>(_Arg);
		return ret;
	}

	template <class _Ty>
	constexpr _Ty&& forward_mine(std::remove_reference_t<_Ty>&& _Arg) noexcept { // forward an lvalue as either an lvalue or an rvalue
		return static_cast<_Ty&&>(_Arg);
	}

	int retInt()
	{
		return 6;
	}
	void useForward()
	{
		int x = 5;
		int& p = x;
		decltype(auto) re = static_cast<int&&>(x);
		decltype(auto) m = std::move(5);
		decltype(auto) r = forward_mine<int&>(x);
		decltype(auto) ret = forward_mine<int>(5);
		//auto ret2 = forward_mine(retInt);
	}

	template<typename T>
	decltype(auto) f(T&& val)
	{
		using rawVal = std::decay<T>::type;
		rawVal* tmp = new rawVal{ std::forward<T>(val) };
		return tmp;
	}

	void use()
	{
		useForward();
		int x = 0;
		int& y = x;
		int vec[5] {1,2,3,4,5};
		accept(vec);
		accept(retInt);
		decltype(auto) a = f(vec);
		decltype(auto) b = f(5);
		decltype(auto) c = f(retInt);
		decltype(auto) d = f(y);

		auto x0= (*a)[0];
		auto xx = (*a)[1];

		(*b) = 15;

		auto xxx = (*c)();

		delete a;
		delete b;
		delete c;
	}

	namespace impl
	{
		template< class T >
		struct decay {
		private:
			typedef typename std::remove_reference<T>::type U;
		public:
			typedef typename std::conditional<
				std::is_array<U>::value,
				typename std::remove_extent<U>::type*,
				typename std::conditional<
				std::is_function<U>::value,
				typename std::add_pointer<U>::type,
				typename std::remove_cv<U>::type
				>::type
			>::type type;
		};

		#include <type_traits>

		template <typename T, typename U>
		constexpr bool is_decay_equ = std::is_same_v<std::decay_t<T>, U>;

		void main()
		{
			static_assert(
				is_decay_equ<int, int> &&
				!is_decay_equ<int, float> &&
				is_decay_equ<int&, int> &&
				is_decay_equ<int&&, int> &&
				is_decay_equ<const int&, int> &&
				is_decay_equ<int[2], int*> &&
				!is_decay_equ<int[4][2], int*> &&
				!is_decay_equ<int[4][2], int**> &&
				is_decay_equ<int[4][2], int(*)[2]> &&
				is_decay_equ<int(int), int(*)(int)>
				);
		}

		namespace rvalue
		{
			static_assert(std::is_same_v<std::add_rvalue_reference_t<int>, int&&>);
			static_assert(std::is_same_v<std::add_rvalue_reference_t<int&>, int&>); // <--
			static_assert(std::is_same_v<std::add_rvalue_reference_t<int&&>, int&&>);
			using lvalue_ref = int&;
			using rvalue_ref = int&&;
			static_assert(std::is_same_v<lvalue_ref&, int&>);
			static_assert(std::is_same_v<lvalue_ref&&, int&>);
			static_assert(std::is_same_v<rvalue_ref&, int&>);
			static_assert(std::is_same_v<rvalue_ref&&, int&&>);
		}
	}
}

template<typename T> auto f0(T&& val)
{
	using raw_type = std::decay_t<T>;
	raw_type* tmp = new raw_type{ std::forward<T>(val) };
	return tmp;
}


template<typename T> auto f1(T&& val) {
	using raw = T;
	raw* tmp = new raw{ std::forward<T>(val) };
	return tmp;
}

template<typename T>
struct TD;


template<typename T> auto f2(T&& val) {
	using raw = std::remove_reference_t<T>;
	
	//using type = std::add_pointer_t<std::remove_extent_t<raw>>;
	constexpr bool same = std::is_same_v<raw, int[5]>;
	//static_assert(same);
	//raw* r = new int[5](val);
	//raw * t = new raw(val); // new raw(std::forward<T>(val));																	// val == int[] == int*
	return 10;
}

template<typename T> auto f3(T&& val) {
	constexpr bool same1 = std::is_same_v<decltype(val), double(&)(double)>;
	static_assert(same1);
	using raw = std::remove_reference_t<T>;
	using type = std::add_pointer_t<raw>;
	constexpr bool same = std::is_same_v<type, double(*)(double)>;
	static_assert(same);
	type* t = new type(val);		// val == double(&)(double)
	return t;
}

template<typename TIn>
double fun(const TIn& in)
{
	auto a = in.template Get<A>();
	auto b = in.template Get<B>();
	auto c = in.template Get<C>();

	return c(b);
	//return a ? b : c;
}

double func(double i) { return i * 2; }

void useVarTypeDict()
{
	double val = 0;
	double aa = 0;
	double overcero = aa / val;
	double d = 10 / aa;
	double ee = 2 * exp2(-10);
	auto res = overcero <=> 10.55;
	bool is = is_eq(res);
	bool isnot = is_neq(res);
	bool isless = is_lt(res);
	bool ismore = is_gt(res);
	bool ismore_or_eq = is_gteq(res);
	if( d <=> 10.55 > 0)
	{
		std::cout << d << std::endl;
	}
	
	int vec[5];
	auto m = f0(vec);
	//auto x = f1(vec);
	auto y = f2(vec);
	auto z = f3(func);

	testing::fillContainer();

	constexpr size_t p = testing::Tag2PosT<C, A, B, D>::Pos;
	constexpr size_t pos = Tag2Pos<C, A, B, C>();
	auto ret = fun(VarTypeDict<A, B, C>::Create().Set<A>(true).Set<B>(1.55).Set<C>(func));
	using type = decltype(VarTypeDict<A, B, C>::Create().Set<A>(true).Set<B>(1.55).Set<C>(func));
	type* pp;
}

namespace requisitos
{
	// requirementsCheckSFINAE.cpp
	namespace enable_if
	{
#include <type_traits>

		template<typename T,
			typename std::enable_if<std::is_integral<T>::value, T>::type = 0>
		T moduloOf(T t) {
			return t % 5;
		}

		void main() {

			//auto res = moduloOf(5.5);

		}
	}
	// requirementsCheckConcepts.cpp

#include <concepts>

	std::integral auto moduloOf(std::integral auto t) {
		return t % 5;
	}

	void main() {

		//auto res = moduloOf(5.5);

	}

}


#include <compare>

void comparable()
{
	using func = int(*(*)(double))[3];

	//func* bar = new func;
	//auto b = bar[0](5.55);

	int(*(*foo)(double))[3] = nullptr;

	//auto c = (*(foo))(5.55);

	using foo_t = decltype(foo);
	foo_t p;

	//double d = 10 / 0;
	//std::strong_ordering::equal()
}


template<typename T>
concept Addable = requires (T a, T b)
{
	a + b;
};



template<typename T>
struct Other;


template<>
struct Other<std::vector<int>> {};


template<typename T>
concept TypeRequirement = requires
{
	typename T::value_type;
	typename Other<T>;
};

void useTR(TypeRequirement auto tr)
{
	
}



void useTypeRequirement()
{
	TypeRequirement auto myVec = std::vector<int>{ 1,2,3 };
	TypeRequirement auto myList = std::list<int>{ 1,2,3 };
	//Other<std::list<int>> other;
	Other<std::vector<int>> other_vec;
	useTR(std::list<int>{ 1, 2, 3 });

}







template<class T, class U = T>
concept Swappable = requires(T && t, U && u)
{
	swap(std::forward<T>(t), std::forward<U>(u));
	swap(std::forward<U>(u), std::forward<T>(t));
};


//template<typename T>
//concept vectorial = requires template<typename U> std::is_same_v<T, std::vector<U>>;

template<typename T>
inline constexpr bool is_a_vector = std::_Is_specialization<T, std::vector>::value;


template<typename T>
concept is_esp_vec = std::_Is_specialization<T, std::vector>::value;


template<typename T>
concept Semi = requires
{
	requires is_a_vector<T>;

};




template<typename T>
struct S;


template<typename T>
using Ref = T&;

template<typename T>
concept C = requires
{
	typename T::inner; // required nested member name
	typename S<T>;     // required class template specialization
	typename Ref<T>;   // required alias template substitution
};

template<class T, class U>
using CommonType = std::common_type_t<T, U>;

template<class T, class U>
concept Common = requires (T && t, U && u)
{
	typename CommonType<T, U>; // CommonType<T, U> is valid and names a type
	{ CommonType<T, U>{std::forward<T>(t)} };
	{ CommonType<T, U>{std::forward<U>(u)} };
};

void useVect()
{
	constexpr bool is = is_a_vector<std::vector<int>>;
	constexpr bool is_list = is_a_vector<std::list<int>>;



	is_esp_vec auto v = std::vector<int>{ 1,2,3 };
	//is_esp_vec auto w = std::list<int>{ 1,2,3 };
	Semi auto s = std::vector<int>{ 1,2,3 };
	//Semi auto t = std::list<int>{ 1,2,3 };
	//vectorial auto vec = std::vector<int>{ 1,2,3 };
	//vectorial auto list = std::list<int>{ 1,2,3 };
}





template<typename T>
concept C2 = requires(T x)
{
	// the expression *x must be valid
	// AND the type T::inner must be valid
	// AND the result of *x must be convertible to T::inner
	{*x} -> std::convertible_to<typename T::inner>;

	// the expression x + 1 must be valid
	// AND std::same_as<decltype((x + 1)), int> must be satisfied
	// i.e., (x + 1) must be a prvalue of type int
	{x + 1} -> std::same_as<int>;

	// the expression x * 1 must be valid
	// AND its result must be convertible to T
	{x * 1} -> std::convertible_to<T>;
};

#if 0


template<class T>
concept Semiregular = DefaultConstructible<T> &&
CopyConstructible<T> && Destructible<T> && CopyAssignable<T> &&
	requires(T a, size_t n)
{
	requires Same<T*, decltype(&a)>; // nested: "Same<...> evaluates to true"
{ a.~T() } noexcept; // compound: "a.~T()" is a valid expression that doesn't throw
	requires Same<T*, decltype(new T)>; // nested: "Same<...> evaluates to true"
	requires Same<T*, decltype(new T[n])>; // nested
{ delete new T }; // compound
{ delete new T[n] }; // compound
};




template<typename T>
concept Addable = requires (T x) { x + x; }; // requires-expression

template<typename T> requires Addable<T> // requires-clause, not requires-expression
T add(T a, T b) { return a + b; }

template<typename T>
	requires requires (T x) { x + x; } // ad-hoc constraint, note keyword used twice
T add(T a, T b) { return a + b; }

#endif



template<typename T>
struct isSemiRegular : std::integral_constant<bool,
									std::is_default_constructible<T>::value &&
									std::is_copy_constructible<T>::value &&
									std::is_copy_assignable<T>::value &&
									std::is_move_constructible<T>::value &&
									std::is_move_assignable<T>::value &&
									std::is_destructible<T>::value &&
									std::is_swappable<T>::value> {};


template<typename T>
concept SemiRegular = isSemiRegular<T>::value;


template<typename T>
concept Equal =
	requires(T a, T b) {
		{ a == b } -> std::convertible_to<bool>;
		{ a != b } -> std::convertible_to<bool>;
};


template<typename T>
concept Regular = Equal<T> && SemiRegular<T>;




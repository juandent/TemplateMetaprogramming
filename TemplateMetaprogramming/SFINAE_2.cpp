// #include "stdafx.h"
#include <type_traits>
#include <algorithm>
#include <list>
#include <vector>

namespace no_enable_if
{
	struct have_sort
	{
		char c;
	};

	struct have_range
	{
		char d;
		have_sort  e;
	};

	struct have_nothing
	{
		char e;
		have_range r;
	};


	template<typename T> have_sort test_sort(decltype(&T::sort), decltype(&T::sort));
	template<typename T> have_range test_sort(decltype(&T::begin), decltype(&T::end));
	template<typename T> have_nothing test_sort(...);

	template<typename T, size_t s>
	struct fast_sort_helper;

	template<typename T>
	struct fast_sort_helper<T, sizeof(have_sort)>
	{
		static void fast_sort(T& x)
		{
			x.sort();
		}
	};

	template<typename T>
	struct fast_sort_helper<T, sizeof(have_range)>
	{
		static void fast_sort(T& x)
		{
			std::sort(x.begin(), x.end());
		}
	};


	template<typename T>
	struct fast_sort_helper<T, sizeof(have_nothing)>
	{
		static void fast_sort(T& x)
		{
			static_assert(sizeof(T) < 0, "No sorting available!");
		}
	};



	template<typename T>
	void fast_sort(T& x)
	{
		fast_sort_helper<T, sizeof(test_sort<T>(0, 0))>::fast_sort(x);
	}

	class A
	{
	public:
		void sort() {}
	};

	class B
	{
		int data[10];
	public:
		int* begin() { return data; }
		int* end() { return data + 10; }
	};

	class C
	{
	public:
		void f() {}
	};

	void useFastSort()
	{
		A a;
		fast_sort(a);
		B b;
		fast_sort(b);
		C c;
		// fast_sort(c);


	}
}

namespace useEnableIf
{
	// template <bool _Test, class _Ty = void>
	// struct enable_if // no member "type" when !_Test
	// {};
	//
	// template <class _Ty>
	// struct enable_if<true, _Ty> { // type is _Ty for _Test
	// 	using type = _Ty;
	// };

	struct have_sort
	{
		char c;
	};

	struct have_range
	{
		char d;
		have_sort  e;
	};

	struct have_nothing
	{
		char e;
		have_range r;
	};


	template<typename T> char test_sort(decltype(&T::sort), decltype(&T::sort));
	template<typename T> long test_sort(decltype(&T::begin), decltype(&T::end));
	// template<typename T> have_nothing test_sort(...);


	template<typename T>
	constexpr size_t size_test_sort = sizeof(test_sort<T>(NULL, NULL));


	template<typename T>
	typename std::enable_if< size_test_sort<T> == sizeof(long)>::type fast_sort(T& x)
	{
		std::sort(x.begin(), x.end());
	}

	template<typename T>
	typename std::enable_if< size_test_sort<T> == sizeof(char)>::type fast_sort(T& x)
	{
		x.sort();
	}

	class A
	{
	public:
		void sort() {}
	};

	class B
	{
		int data[10];
	public:
		int* begin() { return data; }
		int* end() { return data + 10; }
	};

	class C
	{
	public:
		void f() {}
	};


	void useFastSort()
	{
		std::enable_if<true, int>::type * p = nullptr;
		// enable_if<std::is_class<int>::value>::type* q = nullptr;
		A a;

		constexpr size_t s = size_test_sort<A>;
		constexpr size_t ss = size_test_sort<B>;

		constexpr auto sizeA = sizeof(test_sort<A>(NULL, NULL));
		fast_sort(a);
		B b;
		constexpr auto sizeB = sizeof(test_sort<B>(NULL, NULL));
		fast_sort(b);
		// C c;
		// fast_sort(c);


	}
}

// template< class T >
// class Y {
//
// public:
// 	template < typename = typename std::enable_if< std::is_class<T>::value>::type >
// 	T foo() {
// 		return 10;
// 	}
// 	template < typename = typename std::enable_if< ! std::is_class<T>::value>::type >
// 	T foo() {
// 		return 10;
// 	}
//
// };


class foo;
class bar;

template<class T>
struct is_bar
{
	template<class Q = T>
	typename std::enable_if<std::is_same<Q, bar>::value, bool>::type check()
	{
		return true;
	}

	template<class Q = T>
	typename std::enable_if<!std::is_same<Q, bar>::value, bool>::type check()
	{
		return false;
	}
};


void useIs_bar()
{
	is_bar<bar> bar_is_bar;
	bar_is_bar.check<>();

}


namespace options_3
{
	struct yes { char a; };
	struct no { char a[2]; };

	template<typename T> yes test_have_sort(decltype(static_cast<void (T::*)()>(&T::sort)));
	template<typename T> no  test_have_sort(...);

	template<typename T> yes test_have_range(
													decltype(static_cast<typename T::iterator (T::*)()>(&T::begin)),
													decltype(static_cast<typename T::iterator (T::*)()>(&T::end)));
	template<typename T> no test_have_range(...);

	template<typename T, bool has_sort, bool has_range>
	struct sort_helper;

	template<typename T>
	struct sort_helper<T, true, true>
	{
		static void fast_sort(T& x)
		{
			x.sort();
		}
	};

	template<typename T>
	struct sort_helper<T, true, false>
	{
		static void fast_sort(T& x)
		{
			x.sort();
		}
	};

	template<typename T>
	struct sort_helper<T, false, true>
	{
		static void fast_sort(T& x)
		{
			std::sort(x.begin(), x.end());
		}
	};

	template<typename T>
	struct sort_helper<T, false, false>
	{
		static void fast_sort(T& x)
		{
			static_assert(sizeof(T) < 0, "No sort available!");
		}
	};

	template<typename T>
	void fast_sort(T& x)
	{
		sort_helper<T,
			sizeof(test_have_sort<T>(NULL)) == sizeof(yes),
			sizeof(test_have_range<T>(NULL, NULL)) == sizeof(yes)>::fast_sort(x);
	}

	template<typename T, size_t N>
	void fast_sort(T(&x)[N])
	{
		std::sort(x, x + N);
	}

	void useFastSort()
	{
		char x[3];
		std::list<int> l;
		std::vector<int> v;
		fast_sort(l);
		fast_sort(v);
	}

}

namespace moreSFINAE
{
	struct yes { char a; };
	struct no { char a[2]; };

	// template<typename T>
	// auto have_star_equal(const T& x, size_t n) -> decltype(const_cast<T&>(x) *= n, yes{});
	template<typename T>
	auto have_star_equal(T x, size_t n) -> decltype(x *= n, yes{});

	no have_star_equal(...);

	template<typename T>
	auto have_star(const T& x, size_t n) -> decltype(x* n, yes{});
	no have_star(...);

	template<typename T, bool has_star_equal, bool has_star>
	struct increase_helper;


	template<typename T>
	struct increase_helper<T,true,true>
	{
		static auto increase(const T& x, size_t n)
		{
			return x * n;
		}
	};

	template<typename T>
	struct increase_helper<T, true, false>
	{
		static auto increase(const T& x, size_t n)
		{
			T y{ x };
			return y *= n;
		}
	};

	template<typename T>
	struct increase_helper<T, false, true>
	{
		static auto increase(const T& x, size_t n)
		{
			return x * n;
		}
	};

	template<typename T>
	struct increase_helper<T, false, false>
	{
		static auto increase(const T& x, size_t n)
		{
			static_assert(sizeof(T) < 0);
		}
	};

	template<typename T>
	void increase(const T& x, size_t n)
	{
		increase_helper<T,
			sizeof(have_star_equal(x, n)) == sizeof(yes),
			sizeof(have_star(x, n)) == sizeof(yes)>::increase(x, n);
	}

	struct AA
	{
		int m_i;
		AA(int i) : m_i{i} {}
		AA(const AA& a) : m_i{a.m_i} {}
		AA& operator*=(int n)
		{
			m_i *= n;
			return *this;
		}
	};

	void useIncrease()
	{
		const int x = 80;
		int n = 5;
		// int(x) += n;

		increase(x, n);

		constexpr size_t s = sizeof(have_star_equal(x, n));

		AA a{ 5 };
		constexpr size_t t = sizeof(have_star_equal(a, n));
	}
}

namespace withTrueType
{
	template<typename T>
	auto have_star(const T& x, size_t n) -> decltype(x * n, std::true_type{});
	std::false_type have_star(...);

	template<typename T>
	auto have_star_equal(T x, size_t n) -> decltype(x *= n, std::true_type{});
	std::false_type have_star_equal(...);

	template<typename T>
	auto have_plus(const T& x) -> decltype(x + x, std::true_type{});
	std::false_type have_plus(...);

	template<typename T, bool have_star, bool have_star_equal, bool have_plus>
	struct increase_helper;

	template<typename T, bool have_star_equal, bool have_plus>
	struct increase_helper<T, true, have_star_equal, have_plus>
	{
		static auto f(const T& x, size_t n)
		{
			return x * n;
		}
	};

	template<typename T, bool have_plus>
	struct increase_helper<T, false, true, have_plus>
	{
		static auto f(const T& x, size_t n)
		{
			T y(x);
			return y *= n;
		}
	};


	template<typename T>
	struct increase_helper<T, false, false, true>
	{
		static auto f(const T& x, size_t n)
		{
			T y(x);
			for (int i = 1; i < n; ++i)
				y = y + y;
			return y *= n;
		}
	};

	template<typename T>
	auto increase( const T& x, size_t n )
	{
		return increase_helper<T,
			decltype(have_star(x, n))::value,
			decltype(have_star_equal(x, n))::value,
			decltype(have_plus(x))::value >::f(x, n);
	}

	void useIncrease()
	{
		int x = 10, n = 4;
		size_t res = increase(x, n);

	}
}

namespace withFramework
{

	template<typename Lambda>
	struct is_valid_helper
	{
		template<typename LambdaArgs>
		constexpr auto test(int)-> decltype(std::declval<Lambda>() (std::declval<LambdaArgs>()), std::true_type{})
		{
			return std::true_type{};
		}
		template<typename LambdaArgs>
		constexpr std::false_type test(...)
		{
			return std::false_type{};
		}
		template<typename LambdaArgs>
		constexpr auto operator()(const LambdaArgs& )
		{
			return this->test<LambdaArgs>(0);
		}
	};

	template<typename Lambda>
	constexpr auto is_valid( const Lambda&)
	{
		return is_valid_helper<Lambda>();
	}

	auto is_assignable = is_valid([](auto&& x)->decltype(x = x)	{});

	struct A
	{
		// A& operator=(const A& other) = delete;
	};

	// using A = int;
	void my_function( const A& a) 
	{
		static_assert(decltype(is_assignable(a))::value, "A is not assignable");
	}

	template<typename T>
	struct IsAssignable
	{
		static constexpr bool value = decltype(is_assignable(std::declval<T>()))::value;
	};

	struct B
	{
		int m_i;
		B(int i =0) : m_i{1} {}
		B& operator=(const B& r)
		{
			m_i = r.m_i;
			return *this;
		}
	};

	B b;
	constexpr bool is = decltype(is_assignable(b))::value;

	void useFramework()
	{
		A a;
		static_assert(IsAssignable<A>::value);
		my_function(a);
	}
}


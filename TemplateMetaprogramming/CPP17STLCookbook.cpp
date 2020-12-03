#include "stdafx.h"

#include <utility>
#include <set>
#include <deque>
#include <list>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <numeric>

void autoDeductionOfTemplate()		// READY IN VS 2017 15.7.1
{
	std::pair my_pair{ 123, "abc" };
	std::remove_reference<decltype("abc")>::type xx{"abc" };
	std::pair<int, const char* const> other_pair{ 123, (char* const)"abc" };
}


template<typename T>
struct sum
{
	T value;

	template<typename ...Ts>
	sum(Ts&& ... values) : value{ (values + ...) } {}

};

// not yet in VS 2017
//template<typename...Ts>
//sum(Ts&&...ts)->sum<std::common_type_t<Ts...>>;


template<typename T>
class addable
{
	T val;
public:
	addable(T v) : val{ v } {}

	template<typename U>
	T add(U x) const
	{
		if constexpr(std::is_same_v<T, std::vector<U>>)
		{
			auto copy{ val };
			for (auto& n : copy)
			{
				n += x;
			}
			return copy;
		}
		else
		{
			return val + x;
		}
	}
};

	void useAddable()
	{
		std::vector<int> v{ 1,2,3,4 };
		int p = 'a';
		auto ad = addable<int>(p);
		auto xx = ad.add('b');

		auto res = addable<std::vector<int>>{v}.add(10);
	}

	using namespace std;

	template<typename C, typename T>
	void insert_sorted(C& v, const T& item)
	{
		const auto iterator_pos{ lower_bound(begin(v), end(v), item) };
		v.insert(iterator_pos, item);
	}

		
	//mbozzi - cplusplus.com

	template <template <typename...> class, typename>
	struct is_instance_of : std::false_type {};

	template <template <typename...> class Tm, typename... Ts>
	struct is_instance_of<Tm, Tm<Ts...>> : std::true_type {};

	template <typename T>
	constexpr bool is_instance_of_set = is_instance_of<std::set, T>::value;

	static_assert(is_instance_of_set<std::set<int>>);
	static_assert(!is_instance_of_set<std::vector<int>>);


	void useSortedInserting()
	{
		using Container = set<string>;
		Container v{ "Juan", "Leslie", "Kisha" };

		if constexpr(!is_same_v < Container, set<string>> && !is_same_v<Container, list<string>>)
		{
			assert(!is_sorted(v.begin(), v.end()));
			sort(v.begin(), v.end());
			assert(is_sorted(v.begin(), v.end()));
		}

		insert_sorted(v, "Ana");
		insert_sorted(v, "Julia");

		for (auto& it : v)
		{
			cout << it << ", ";
		}
		cout << endl;
	}


	void insertionWithHints()
	{
		std::unordered_map<string, size_t> m{ {"b",1}, {"c",2}, {"d",3} };

		auto insert_iter{ std::end(m) };

		for (const auto& s : { "z", "y", "x", "w" })
		{
			insert_iter = m.insert(insert_iter, { s,1 });
		}

		m.insert(std::end(m), { "a", 1 });

		for (const auto&[key, value] : m)
		{
			cout << "\"" << key << "\"" << "\":" << value << ", ";
		}
		cout << endl;
	}



	namespace PolymorphyViaStd_Function
	{
		template<typename Container>
		static auto consumer(Container& container)
		{
			return [&](auto value) {
				container.push_back(value);
			};
		}

		template<typename Container>
		static void print(const Container& c)
		{
			for (auto i : c)
			{
				std::cout << i << ", ";
			}
			std::cout << "\n";
		}

		void main()
		{
			using namespace std;

			deque<int> d;
			list<int> l;
			vector<int> v;


			const vector<function<void(int)>> consumers
			{
				consumer(d), consumer(l), consumer(v)
			};

			for (auto i = 0u; i < 10u; ++i)
			{
				for (auto& consume : consumers)
				{
					consume(i);
				}
			}

			print(d);
			print(l);
			print(v);

		}

	}
	namespace FunctionConcat
	{
		// composing functions by concatenation (pg 146)

		template<typename T, typename ...Ts>
		auto concat(T t, Ts ... ts)
		{
			if constexpr(sizeof...(ts) > 0)
			{
				return [=](auto... parameters)
				{
					return t(concat(ts...)(parameters...));
				};
			}
			else
			{
				return [=](auto ... parameters)
				{
					return t(parameters...);
				};
			}
		}

		void useConcat()
		{
			auto twice([](int i) {return i * 2; });
			auto thrice([](int i) {return i * 3; });
			auto combined(concat(twice, thrice, plus<int>{}));

			cout << combined(2, 3) << endl;
		}
	}

	namespace CombineFunctions
	{
		static bool begins_with_a(const std::string& s)
		{
			return s.find("a") == 0;
		}

		static bool ends_with_b(const std::string& s)
		{
			return s.rfind("b") == s.length() - 1;
		}

		template<typename A, typename B, typename BinaryOp>
		auto combine(BinaryOp op, A a, B b)
		{
			return [=](auto param)
			{
				return op(a(param), b(param));
			};
		}

		void useCombine()
		{
			using namespace std;

			auto a_xxx_b = combine(logical_and<>{}, begins_with_a, ends_with_b);

			//cin.unsetf(ios_base::skipws);

#if 1
			vector<int> va;
			copy(istream_iterator<int>{cin}, istream_iterator<int>{},
				back_inserter(va));
#endif
			auto f = cin.flags();
			auto eof = cin.eof();
			auto bad = cin.bad();
			auto fail = cin.fail();
			auto good = cin.good();

			cin.clear();
			good = cin.good();

			//cin >> skipws;

			vector<string> v;
			copy_if(istream_iterator<string>{cin}, istream_iterator<string>{},
				back_inserter(v), begins_with_a);

			copy(begin(v), end(v), ostream_iterator<string>{cout, ", "});
			cout << endl;

			cin.clear();
			cin >> skipws;


			copy_if(istream_iterator<string>{cin}, istream_iterator<string>{},
				ostream_iterator<string>{cout, ", "},
				a_xxx_b);

			cout << endl;
		}
	}
	

	namespace CallingMultipleFunctionsWithSameInput
	{
		// calling multiple functions with the same input

#if 0
		static auto multicall(auto ...functions)
		{
			return [=](auto x)
			{
				(void)std::initializer_list<int>{
					((void)functions(x), 0)...
				};
			};
		}
#else

		template<typename ...functions>
		auto multicall(functions...fs)
		{
			return [=](auto x)
			{
				(void)std::initializer_list<int>{
					((void)fs(x), 0)...
				};
			};
		}
#endif

		template<typename F, typename ...XS>
		static auto for_each(F f, XS...xs)
		{
			(void)std::initializer_list<int>{
				((void)f(xs), 0)...
			};
		}
		static auto brace_print(char a, char b)
		{
			return [=](auto x)
			{
				std::cout << a << x << b << ", ";
			};
		}

		void useMulti()
		{
			// define functions

			auto f = brace_print('(', ')');
			auto g = brace_print('[', ']');
			auto h = brace_print('{', '}');
			auto nl = [](auto ) { std::cout << "\n"; };

			auto call_fgh = multicall(f, g , h, nl);

			for_each(call_fgh, 1 , 2, 3, 4, 5);

		}
	}


	namespace Transform_if_with_lambdas
	{
		template<typename T>
		auto map(T fn)
		{
			return [=](auto reduce_fn) {
				return [=](auto accum, auto input)
				{
					return reduce_fn(accum, fn(input));
				};
			};
		}

		template<typename T>
		auto filter(T predicate)
		{
			return [=](auto reduce_fn)
			{
				return [=](auto accum, auto input)
				{
					if (predicate(input))
					{
						return reduce_fn(accum, input);
					}
					else
					{
						return accum;
					}
				};
			};
		}

		istream_iterator<int> it_end;

		// filter's predicate
		auto even = [](int i) { return i % 2 == 0; };
		// map's transform
		auto twice = [](int i) { return i * 2; };
		// 
		auto copy_and_advance = [](auto it, auto input)
		{
			*it = input;	// "accumulates" into iterator
			return ++it;	// moves to next element
		};

		void simplestAccumulate()
		{
			vector<int> v{ 1,2,3,4,5 };

			auto res = accumulate(v.cbegin(), v.cend(), 0, std::plus<int>{});

			cout << res << endl;
		}
		void accumulateIntoAnOutputIterator()
		{
			/*
			template<class _InIt,
			class _Ty,
			class _Fn>
			_Ty accumulate(_InIt _First, const _InIt _Last, _Ty _Val, _Fn _Func)
			*/

			auto res = accumulate(istream_iterator<int>{ cin }, it_end,
				ostream_iterator<int>{cout, ", "}, copy_and_advance);

			cout << endl;

		}
		void useTransform_if()
		{
			cin.clear();
			cin >> skipws;
			//int integer;
			//cin >> integer;
			//cin.getline

			accumulate(istream_iterator<int>{ cin }, it_end,
				ostream_iterator<int>{cout, ", "},
				filter(even) (			// predicate is even, returns function expecting a reduce_fn
										// which is filled by return type of map(twice)
					map(twice) (		// input transforming function is 'twice', 
										// expecting a reduce_fn which is copy_and_advance
										
						copy_and_advance
						)
					));
			cout << "\n";

		}
	}

	// pg 163. C++ 17 STL Cookbook
	namespace Cartesian_product_at_compile_time
	{
		static void print(int x, int y)
		{
			cout << "(" << x << ", " << y << ")\n";
		}


		void useCartesian()
		{
			constexpr auto call_cart = [=](auto f, auto x, auto ...rest) constexpr
			{
				(void)initializer_list<int>{
					(((x < rest)
						? (void)f(x, rest)
						: (void)0), 0)...
				};
			};

			constexpr auto cartesian = [=](auto...xs) constexpr
			{
				return[=](auto f) constexpr {
					(void)initializer_list<int>{
						((void)call_cart(f, xs, xs...), 0)...
					};
				};
			};


			auto print_cartesian(cartesian(1, 2, 3));

			print_cartesian(print);

		}


	}



#include "stdafx.h"

using namespace std;

namespace LambdaImpl_1
{
	class ALambda
	{
		std::string name;
	public:
		ALambda(const std::string name) : name{ name } {}


		auto operator()(char a, char b)
		{
			return a + name + b;
		}
	};


	void useALambda()
	{
		ALambda lam{ "juan" };

		std::cout << lam('a', 'b') << std::endl;

	}
}
namespace LambdaImpl_2
{
#if 0
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

	namespace UsingInitializerList
	{

		template<typename...functions>
		class Multicall
		{
			std::tuple<functions...> pfs;
		public:
			Multicall(functions...fs) : pfs{ std::tuple<functions...>(fs...) }
			{
			}

			template<typename X>
			void operator() (X x)
			{
				do_multicall(x, pfs, std::index_sequence_for<functions...>());
			}

			//The helper method.
			template<typename X, std::size_t... Is>
			void do_multicall(X x, const std::tuple<functions...>& tuple, std::index_sequence<Is...>&& seq) {

				std::initializer_list<int>
				{
					(std::get<Is>(tuple)(x), 0)...
				};
			}
		};

	}

	namespace UsingRecursion
	{

		template<typename...functions>
		class Multicall
		{
			std::tuple<functions...> pfs;
		public:
			Multicall(functions...fs) : pfs{ std::tuple<functions...>(fs...) }
			{
			}

			template<typename X>
			void operator() (X x)
			{
				invoke_pfs<0>(x);
			}
		private:

			//The helper method.
			template<size_t I, typename X>
			void invoke_pfs(X x) {
				get<I>(pfs)(x);

				if constexpr (I + 1 < std::tuple_size<decltype(pfs)>())
				{
					invoke_pfs<I + 1>(x);
				}
			}
		};


	}

	namespace JLBorges
	{
		template < typename... FN > struct multi_call
		{
			multi_call() = delete;
			explicit multi_call(FN... fn) : functions{ fn... } {}

			template < typename... ARGS >
			void operator() (ARGS&&... args) const
			{
				call< void, std::tuple_size< decltype(functions) >::value - 1, std::tuple<FN...> >
				{ functions, std::forward<ARGS>(args)... };
			}

		private:

			const std::tuple<FN...> functions;

			/////////// helper template to extract tuple elements and call ////////////
			template < typename, std::size_t, typename... > struct call;

			template < typename T, std::size_t N, typename... ITEMS >
			struct call< T, N, std::tuple<ITEMS...> > : call< T, N - 1, std::tuple<ITEMS...> >
			{
				template < typename... ARGS >
				call(const std::tuple<ITEMS...>& tup, ARGS&&... args)
					: call< T, N - 1, std::tuple<ITEMS...> >(tup, std::forward<ARGS>(args)...)
				{
					std::get<N>(tup)(std::forward<ARGS>(args)...);
				}
			};

			template < typename T, typename... ITEMS >
			struct call< T, 0, std::tuple<ITEMS...> >
			{
				template < typename... ARGS >
				call(const std::tuple<ITEMS...>& tup, ARGS&&... args)
				{
					std::get<0>(tup)(std::forward<ARGS>(args)...);
				}
			};
		};

	}

	namespace CPP_17
	{
		template <typename ...Fs>
		class Multicall {
		public:
			Multicall(Fs&&... fs) : pfs{ fs... } {}

			template <typename X>
			void operator() (X&& x) 
			{
				std::apply([x](auto&&...f) {
					(static_cast<void>(std::forward<decltype(f)>(f)(x)), ...);
				}, pfs);


				///////std::apply([x](auto&&... f) { (..., f(x)); }, pfs);
			}

		private:
			std::tuple<Fs...> pfs;
		};
	}

	template<typename function>
	class SingleCall
	{
		function fs;

	public:
		SingleCall(function fs) : fs{ fs } {}

		template<typename X>
		auto operator() (X x)
		{
			return fs(x);
		}

	};


	/// functions
	int twice(int x) {
		std::cout << x << endl;
		return x * x; 
	}
	int thrice(int x) { 
		std::cout << x << endl;
		return x * x*x; 
	}


	void useMulticall()
	{
		UsingInitializerList::Multicall mc(twice, thrice);
		mc(15);

		SingleCall scall(twice);
		auto res = scall(5);


		UsingRecursion::Multicall mcr(twice, thrice);
		mcr(10);


		const JLBorges::multi_call jlbmc
		{
			[](int, int, int) { std::cout << "one\n"; },
			[](double, short, char) { std::cout << "two\n"; },
			[](long, double, int) { std::cout << "three\n"; },
			[](char, char, char) { std::cout << "four\n"; }
		};

		jlbmc('a', 'b', 'c');

		CPP_17::Multicall mc17{ [](int x) { cout << (3 * x) << endl; }, std::function(twice) };

		mc17(20);


			
	}





}

#include <iostream>
#include <compare>
#include <vector>
#include <ranges>
#include <type_traits>
#include <concepts>
#include <optional>
#include <iterator>


//********************************************************
// The following code example is taken from the book
//  C++20 - The Complete Guide
//  by Nicolai M. Josuttis (www.josuttis.com)
//  http://www.cppstd20.com
//
// The code is licensed under a
//  Creative Commons Attribution 4.0 International License
//  http://creativecommons.org/licenses/by/4.0/
//********************************************************


#include <iostream>
#include <vector>
#include <set>
#include <ranges>
#include <atomic>

// concept for container with push_back():
template<typename Coll>
concept SupportsPushBack = requires(Coll coll, Coll::value_type val) {
	coll.push_back(val);
};

// concept to disable narrowing conversions:
template<typename From, typename To>
concept ConvertsWithoutNarrowing =
std::convertible_to<From, To> &&
	requires (From && x) {
		{ std::type_identity_t<To[]>{std::forward<From>(x)} }
		-> std::same_as<To[1]>;
};


// add() for single value:
template<typename Coll, typename T>
	requires ConvertsWithoutNarrowing<T, typename Coll::value_type>
void add(Coll& coll, const T& val)
{
	if constexpr (SupportsPushBack<Coll>) {
		coll.push_back(val);
	}
	else {
		coll.insert(val);
	}
}

// add() for multiple values:
template<typename Coll, std::ranges::input_range T>
	requires ConvertsWithoutNarrowing<std::ranges::range_value_t<T>,
typename Coll::value_type>
void add(Coll& coll, const T& val)
{
	if constexpr (SupportsPushBack<Coll>) {
		coll.insert(coll.end(),
			std::ranges::begin(val), std::ranges::end(val));
	}
	else {
		coll.insert(std::ranges::begin(val), std::ranges::end(val));
	}
}

namespace adds
{
	void main()
	{
		std::vector<int> iVec;
		add(iVec, 42);      // OK: calls push_back() for T being int

		std::set<int> iSet;
		add(iSet, 42);      // OK: calls insert() for T being int

		short s = 42;
		add(iVec, s);       // OK: calls push_back() for T being short

		long long ll = 42;
		//add(iVec, ll);      // ERROR: narrowing
		//add(iVec, 7.7);     // ERROR: narrowing

		std::vector<double> dVec;
		add(dVec, 0.7);      // OK: calls push_back() for floating-point types
		add(dVec, 0.7f);     // OK: calls push_back() for floating-point types
		//add(dVec, 7);        // ERROR: narrowing

		// insert collections:
		add(iVec, iSet);     // OK: insert set elements into a vector
		add(iSet, iVec);     // OK: insert vector elements into a set

		// can even insert raw array:
		int vals[] = { 0, 8, 18 };
		add(iVec, vals);     // OK
		//add(dVec, vals);    // ERROR: narrowing
	}


}


namespace auto_param
{



	auto printColl = [](const auto& coll)
	{
		for (const auto& elem : coll)
		{
			std::cout << elem << "\n";
		}
	};

	void printCollFunc(const auto& coll)
	{
		for (const auto& elem : coll)
		{
			std::cout << elem << "\n";
		}
	}

	void printFunc(const auto& arg)
	{

	}

	auto printLambda = [](const auto& arg)
	{

	};

	void use()
	{
		printFunc("hello");
		printLambda("hello");
	}



	void addValInto(const auto& val, auto& coll)
	{
		coll.push_back(val);
	}

	template<typename Coll>   // Note: different order of template parameters
	requires std::ranges::random_access_range<Coll>
	void addValInto(const auto& val, Coll& coll)
	{
		coll.push_back(val);
	}



	template<typename From, typename To>
	concept ConvertsWithoutNarrowing = requires (From && x)
	{
		std::type_identity_t<To[]>{std::forward<From>(x) } -> std::same_as<To[0]>;
	};


	template<typename Coll, typename T>
	requires ConvertsWithoutNarrowing<T, typename Coll::value_type>
	void add(Coll& coll, const T& val)
	{
		coll.push_back(val);
	}	


	template<typename Coll>
	concept SupportsPushBack = requires (Coll col)
	{
		col.push_back(std::declval<typename Coll::value_type&>());
	};


	template<typename Coll>
	concept SupportsPushBack2 = requires (Coll col)
	{
		col.push_back(std::declval<std::ranges::range_value_t<Coll>>());
	};



	void main()
	{
		using ColColl = int[];
		ColColl col{1,2,3};


		double d{ 3 };

#if 0
//		addValInto<std::vector<int>>(42, coll); 

		//add(coll, 5);
		int i;
		auto wes = std::type_identity_t<ColColl>{ std::forward<int>(i) };
		constexpr bool same_as = std::is_same_v<decltype(wes), ColColl[1]>;

		double x;
		auto res = std::type_identity_t<decltype(coll)>{std::forward<double>(x)};
		int i;
		auto r = std::type_identity_t<ColColl>{i  };

		constexpr bool same = std::is_same_v<decltype(r), ColColl>;


		auto rrr = r[0];

		using t = typename std::type_identity<ColColl>::type;
		t{ x };

		std::vector<int> vec{ x };
#endif


		using my_array = int[];
		auto ss = my_array{ 1,2,3 }[1];

	}



}


template<std::integral T>
class MyType1
{
	
};

template<typename T>
requires requires
{
	typename MyType1<T>;
}
void mytype1(T)
{
}


namespace again
{

	template<std::integral T>
	class MyType1
	{

	};


	//std::hash<MyType1<int>>(MyType1<int>&) = delete;
}


namespace std {

	template<typename T>
	struct hash<MyType1<T>>
	{
		size_t operator()(int t)
		{
			return 2000;
		}
	};


}

	template<typename T>
	concept StdHash = requires
	{
		typename std::hash<T>;
		//std::hash<T>{};
	};

	template<typename T>
	//requires StdHash<T>
	class MyType2
	{

	};

	void done()
	{
		MyType2<MyType1<int>> ds;
		auto h = std::hash<MyType1<long>>();



		std::optional<const int> op = 12;
		const int& x = *op;


		std::optional<int> opp = 12;
		int& y = *opp;


		constexpr bool ask = std::indirectly_readable<decltype(op)>;

		int m = 3;
		int* p = &m;
		const int* pp = &m;

		auto&& mm = *p;
		auto&& mmm = *pp;


		constexpr bool ask2 = std::indirectly_readable<decltype(p)>;

	}

	void useOpt()
	{

		int* const cp = nullptr;
		int* mp = nullptr;
		auto&& mmp = *mp;
		auto&& mcp = *cp;

		static_assert(std::same_as<decltype(*cp), decltype(*mp)>);
		static_assert(std::same_as<decltype(*cp), int&>);
		static_assert(std::same_as<decltype(*mp), int&>);

		std::optional<int> const co;
		std::optional<int> mo;

		auto&& mco = *co;
		auto&& mmo = *mo;
		
		static_assert(!std::same_as<decltype(*co), decltype(*mo)>);
		static_assert(std::same_as<decltype(*mo), int&>);
		static_assert(std::same_as<decltype(*co), int const&>);

	}













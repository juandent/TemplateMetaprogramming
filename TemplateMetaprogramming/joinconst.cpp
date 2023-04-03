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


#include <vector>
#include <array>
#include <cassert>
#include <format>
#include <ranges>
#include <sstream>
#include "printcoll.hpp"


using namespace std::string_literals;


void printConstColl(const auto& coll)
{
	printColl(coll);
}

namespace Cpp20TCG
{
	int left_of_period(double val);
	int left_digits(int val);

	void fooDyn(std::span<int>) {}
	void fooFix(std::span<int, 5>) {}

	std::string leave_digits(const std::string& s)
	{
		std::string str;
		for (auto c : s)
		{
			if (std::isdigit(c) || c == '.')
			{
				str.append(1, c);
			}
		}
		return str;
	}


	void main()
	{
		std::vector<int> rg1{ 1, 2, 3, 4 };
		std::vector<int> rg2{ 0, 8, 15 };
		std::vector<int> rg3{ 5, 4, 3, 2, 1, 0 };
		std::array coll{ rg1, rg2, rg3 };

		printConstColl(coll);
		printConstColl(coll | std::views::join);

		auto collTx = [](const auto& coll) {return coll; };  //->std::add_lvalue_reference_t<decltype(coll)> { return coll; };

		auto lTx = [](const auto& coll) { return coll; };  //->std::add_lvalue_reference_t<decltype(coll)> { return coll; };

		constexpr bool is_same = std::is_same_v<decltype(lTx(rg1)), decltype(rg1)>;

		auto coll2values = coll | std::views::transform(collTx);

		auto c0 = coll2values[0];
		auto& d0 = coll[0];
		bool eq0 = c0 == d0;

		// for(auto& )

		printConstColl(coll2values);
//		printConstColl(coll2values | std::views::join);   // ERROR



		std::span<int, 4> sp{ rg1};
		auto ssp = sp.subspan<1>();
		auto s = ssp.size();
		auto sssp = sp.subspan<1, 2>();
		auto ss = sssp.size();
		auto buffer = as_bytes(sssp);


		{
			std::span<int> sp{ rg1 };	// size == 4
			auto sz = sp.size();
			std::span<int, 4> sp3{ sp };
			int x = sp3[0];
			int y = sp3[1];
			int z = sp3[2];
			int m = sp3[3];
			

		}
		{
			std::vector<int> vec{ 1,2,3,4,5,6,7,8,9,10 };
			std::span<int> spanDyn{ vec.begin(), 5 };
			std::span<int> spanDyn2 = { vec.begin(), 5 };
			std::span<int, 5> spanFix{ vec.begin(),5 };
//			spanFix = spanDyn2;
			// std::span<int, 5> spanFix2 = { vec.begin(),5 };	// std::span<int,5> is explicit ctor

			void fooDyn(std::span<int>);
			void fooFix(std::span<int, 5>);

			fooDyn({ vec.begin(),5 });
			fooDyn(spanDyn);
			fooDyn(spanFix);
			// fooFix({ vec.begin(),5 });	// error
	//		fooFix(spanDyn);			// error
			
		}

		{
			char buffer[5]{};
			auto ret = std::format_to_n(buffer, std::size(buffer) - 1, "{}", 123456.78);
			auto size = ret.size;
			int i = 0;

			std::string str{ "hello" };
			std::string res = std::format("String {} has {} chars", str, str.size());

			const char* p = "Hola";
			p[0];
			// p[1] = 'O';
			constexpr const char* fmt = "{:7X}"; 
			std::cout << std::format(fmt, 42);

			auto s = std::format("{:2>+#010.5}", 400.50);

			assert(s == "222+400.50");

			s = std::format("{:2>+#010.4}", 400.50);

			assert(s  == "2222+400.5");

			s = std::format("{:2>+#010.3}", 400.50);

			assert(s == "22222+400.");


			s = std::format("{:0<7}", "hi");

			assert(s == "hi00000");

			s = std::format("{:.3}", 400.75);

			assert(s == "401");

			s = std::format("{:.2}", 0.75);

			assert(s == "0.75");

			s = std::format("{:.1}", 0.75);

			assert(s == "0.8");

			s = std::format("{:.3}", 0.00000754);

			assert(s == "7.54e-06");

			s = std::format("{:.3}", 0.00754);

			assert(s == "0.00754");

			s = std::format("{:.3}", 0.000754);

			assert(s == "0.000754");

			s = std::format("{:.3}", 0.000075);

			assert(s == "7.5e-05");

			s = std::format("{:.4}", 0.00007542);

			assert(s == "7.542e-05");

			s = std::format("{:.3f}", 0.0075);

			assert( s == "0.007");

			s = std::format("{:.2f}", 0.0075);

			assert(s == "0.01");

			s = std::format("{:.2f}", 0.00075);

			assert(s == "0.00");

			s = std::format("{:.2f}", 1.0075);

			assert(s == "1.01");

			s = std::format("{:&^ #012.2f}", 12345.0075);

			assert(s == "& 12345.01&&");

			s = std::format("{:#012.2f}", 12345.0075);

			assert(s == "000012345.01");


			s = std::format("{:+#012.2f}", 12345.0075);

			s = std::format("{: #012.2f}", 12345.0075);

			assert(s == " 00012345.01");

			s = std::format("{: #012.2f}", -12345.0075);

			assert(s == "-00012345.01");

			s = std::format("{: #04.2f}", -12345.0075);

			assert(s == "-12345.01");

			s = std::format("{: #0.2f}", -12345.0075);

			assert( s == "-12345.01");

			s = std::format("{:012}", -12345.0075);

			s = std::format("{:%< 13}", -12345.0075);

			assert(s == "-12345.0075%%");

			s = std::format("{:+013}", -12345.0075);

			s = std::format("{:+013.2}", -12345.0075);

			assert(s == "-000001.2e+04");

			s = std::format("{:+011.2}", -12345.0075);

			assert(s == "-0001.2e+04");

			s = std::format("{:+011.3}", -12345.0075);

			assert(s == "-001.23e+04"s);

			s = std::format("{:+013.2f}", -12345.0075);

			s = std::format("{:+013.2f}", 12345.0075);

			s = std::format("{: 013.2f}", 12345.0075);

			s = std::format("{:013.2f}", 12345.0075);

			auto sp = std::format("{:#g}", -1.0);


			s = std::format("{:#b} {:#b} {:#b}", 12345, 42, true);

			s = std::format("{:#x} {:#x} {:#x}", 12345, 42, true);

			s = std::format("{:f}", 0.00000012345 );

			s = std::format("{:.10f}", 0.00000012345);

			double d = 0.00000012345678901234567890L;

			s = std::format("{:.16f}", d);

			s = std::format("{:22.20f}", d);

			double dd = 10.00000012345678901234567890L;				 // 10.000000123456789012

			constexpr auto dg = std::numeric_limits<double>::digits10;

			//s = std::format("{:+{}.{:f}f}", dg, dg*2, dg);

			double dbase = 0.00000012345678901234567890L;				 // 0.000000123456789

			for(int power=1; power < 10'000; power *= 10)
			{
				int left = left_digits(dbase);
				s = std::format("{1} after period = '{0:20.{1}f}'", dbase, dg - left);
				dbase += power;
			}

			dd += 1000;
			int left = left_digits(dd );

			s = std::format("{:20.{}f}", dd, dg - left);

			auto digits = leave_digits(s);

			auto re= std::numeric_limits<double>::round_error();

			auto ssss = std::format("{:.10}", dd);

			///assert(ssss == "110.000000123457");

			int j = 0;

			std::istringstream is{"$5,600"};
			is.imbue(std::locale{"en_US"});
			auto loc = is.getloc();
			auto name = loc.name();
			double dou;
			is >> dou;



		}
	}

	int left_of_period(double val)
	{
		int left = static_cast<int>(val);			// 40.4445
		int count = 0;
		while(left)
		{
			left /= 10;
			count++;
		}
		return count;
	}

	int left_digits(int val)
	{
		if (val == 0) return 0;
		return (val != 0 ? 1 : 0) + left_digits(val / 10);
	}

	struct Money
	{
		double value;
		friend std::ostream& operator<<(std::ostream os, Money m)
		{
			os << std::format("{:>}", m.value);
			return os;
		}
	};


	struct A
	{
		int* members;
		A() : members(new int[7]) {}
		~A() { delete[] members; }
		A(const A& o) : members(new int[7])
		{
			for (int i = 0; i < 7; ++i)
				members[i] = o.members[i];
		}
		A(A&& other)
		{
			members = other.members;
			other.members = nullptr;
		}
	};

	A getA()
	{
		return A{};
	}

	void process(const A& ref )
	{
		std::cout << "A&\n";
	}

	void process(A&& ref)
	{
		std::cout << "A&&\n";
		A destination{ std::move(ref) };
	}


	template<typename T>
	void doForwardCorrect(T&& param)
	{
		process(std::forward<T>(param));
	}

	template<typename T>
	void doForwardIncorrect(T param)	// ALWAYS calls process(A&&)
	{
		process(std::forward<T>(param));	// because of forward
		T* p = &param;						// param is now always empty
	}

	template<typename T>
	void doNoForward(T param)			// ALWAYS calls process(const A&)
	{
		process(param);					// because of no forward
	}

	void exerciseForwarding()
	{
		doForwardCorrect(getA());
		A a;
		doForwardCorrect(a);

		doForwardIncorrect(getA());
		doForwardIncorrect(a);
		doNoForward(getA());
		doNoForward(a);
	}

/*
	The name of a variable, function or member
		String literal
		The result of dereferencing a pointer
		The result of a function returned by lvalue reference(type&)
*/

	int& getInt()
	{
		static int value;
		return value;
	}

	void lvalue()
	{
		int arr[4] = { 0,0,0,0 };
		int* p = arr;
		*p = 30;
		getInt() = 50;
	}

}

namespace value_categories
{
	class X {};

	void f(const X& o)	// accepts expression of any category
	{}

	void f(X&& t)		// accepts prvalues and xvalues only, but is a better match
	{}

	void useCategories()
	{
		X v;
		const X c;

		f(v);				// passes a modifiable lvalue to the first f()

		f(c);				// passes an unmodifiable lvalue to the first f()

		f(X{});			// passes a prvalue to second f()

		f(std::move(v));	// passes an xvalue to the second f()
	}
}

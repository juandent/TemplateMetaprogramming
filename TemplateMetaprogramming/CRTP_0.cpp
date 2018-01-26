#include "stdafx.h"

#include "CRTP_0.h"

#include <iostream>

#if 0
namespace JD_first_version
{
	template<typename CharT>
	class MyString : public ObjectCounter<MyString<CharT>> {
		//...
		CharT* pT;
	public:

		template<typename U = std::enable_if_t<std::is_same<CharT, char>::value>>
		MyString()
		{
			pT = "hello";
		}

		template<typename U = std::enable_if_t<std::is_same<CharT, wchar_t>::value>>
		MyString()
		{
			pT = L"hello";
		}

		MyString(CharT* t) : pT{ t }
		{
		}

		~MyString()
		{}

		void print()
		{
			std::cout << "print()" << (pT ? pT : "?") << std::endl;
		}
	};
}
#endif

namespace mbozzi
{
	//#include <type_traits>
	template <typename CharT> class MyString : public ObjectCounter<MyString<CharT>>
	{
		CharT const *pT;

		template <typename T,
			typename = std::enable_if_t<std::is_same<char, T>::value>>
			void assign_impl(int) {
			pT = "hello";
		}
		template <typename T,
			typename = std::enable_if_t<std::is_same<wchar_t, T>::value>>
			void assign_impl(long) {
			pT = L"hello";
		}
		void assign() { return assign_impl<CharT>(0); }

		template<typename T, typename=std::enable_if_t<std::is_same<char,T>::value>>
		void print(char* t = nullptr)
		{
			std::cout << "print()" << (pT ? pT : "?") << std::endl;
		}

		template<typename T, typename = std::enable_if_t<std::is_same<wchar_t, T>::value>>
		void print(wchar_t* t = nullptr)
		{
			if (pT == nullptr)
				std::wcout << L"print()" << std::endl;
			else
				std::wcout << pT << std::endl;
		}

	public:
		MyString() { assign(); }
		MyString(const CharT* t) : pT{ t } {}
		void print()
		{
			print<CharT>();
		}
	};

	int main() {
		MyString<char> x;
		MyString<wchar_t> y;
		return 0;
	}
}

namespace JLBorges	// initialization of data member according to template argument
{
	template < typename CHAR_TYPE > struct my_literal_str  /*: public ObjectCounter<my_literal_str<CHAR_TYPE>>*/  {

		constexpr my_literal_str() : ptr(def_val(static_cast< const CHAR_TYPE* >(nullptr))) {}

		constexpr auto c_str() const { return ptr; }

	private:

		const CHAR_TYPE* ptr;

		static constexpr const char* def_val(const char*) { return "Hello (char)"; }
		static constexpr const wchar_t* def_val(const wchar_t*) { return L"Hello (wchar_t)"; }

		// for types other than char/wchar_t, the default value is nullptr
		static constexpr const CHAR_TYPE* def_val(const void*) { return nullptr; }
	};

	void main() {

		constexpr my_literal_str<char> a;
		std::cout << a.c_str() << '\n'; // Hello (char)

		constexpr my_literal_str<wchar_t> b;
		std::wcout << b.c_str() << L'\n'; // Hello (wchar_t)

		constexpr my_literal_str<int> c;
		std::cout << c.c_str() << '\n'; // nullptr
	}
}

void useObjectCounter()
{
	JLBorges::main();

	using namespace mbozzi;

	MyString<char> s{ "Hello" };
	s.print();
	MyString<char> s1, s2;
	MyString<char> s3{ s1 };
	s1.print();
	MyString<wchar_t> ws;
	std::cout << "num of MyString<char>:    "
		<< MyString<char>::live() << '\n';
	std::cout << "num of MyString<wchar_t>: "
		<< ws.live() << '\n';
}

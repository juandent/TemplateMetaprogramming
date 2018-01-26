#include "stdafx.h"

#include "CRTP_0.h"

#include <iostream>

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

	MyString(CharT* t) : pT{t}
	{
	}

	~MyString()
	{}

	void print()
	{
		std::cout << "print()" << (pT ? pT : "?") << std::endl;
	}
};

void useObjectCounter()
{
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

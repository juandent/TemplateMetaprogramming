#include "stdafx.h"

template<typename T, typename U>
T* Create(const U& arg)
{
	return new T(arg);
}

struct Widget
{
	template<typename U>
	Widget( const U& arg, int) {}
};


// overloading:
template<typename T, typename U>
T* Create( const U& arg, T /*dummy*/)
{
	return new T(arg);
}

template<typename U>
Widget* Create( const U&arg, Widget /*dummy*/)
{
	return Widget(arg,-1);
}


// above very inefficient

template<typename T>
struct Type2Type
{
	using OriginalType = T;
};

// below very efficient, using overloading via type identity

template<typename T, typename U>
T* Create( const U& arg, Type2Type<T>)
{
	return new T(arg);
}

template<typename U>
Widget* Create(const U& arg, Type2Type<Widget>)
{
	return new Widget(arg,-1);
}

void useCreate()
{
	auto p = Create("Hola", Type2Type<std::string>());
	auto w = Create(100, Type2Type<Widget>());
}


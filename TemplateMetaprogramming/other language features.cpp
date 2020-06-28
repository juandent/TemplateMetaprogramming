#include "stdafx.h"


enum MyInt : char {};

MyInt i1{ 42 };
// MyInt i2 = 42;


enum Flags {bit1=1, bit2=2, bit3=4};

// Flags f{ 1 };
//
// Flags f2 = 1;

enum class Weekday {mon,tue,wed,thur,fri,sat,sun};

Weekday w{ 3 };

// Weekday w2 = 3;

enum class Weekday2 : char { mon, tue, wed, thur, fri, sat, sun };

Weekday2 w3{ 3 };



auto a{ 42 };
//auto b{ 1,2,3 };
auto c = { 42 };
auto d = { 34,55,67 };


constexpr auto e = u8'6';
constexpr auto f = '6';

constexpr bool eq = (e == f);

constexpr int ee = e;

void (*fp)() noexcept;

void fMightThrow();
void fNoExcept() noexcept {};


void fpf()
{
	//fp = fMightThrow;

	fp = fNoExcept;
}


class Base
{
public:
	virtual void foo() noexcept {}
};

class Derived : public Base
{
public:
	void foo() noexcept override ;
};



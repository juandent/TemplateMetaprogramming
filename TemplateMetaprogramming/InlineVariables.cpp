#include "stdafx.h"

enum Types {small, medium, large};

class MyClass
{
	static const bool trace = false;
	static const Types Type = small;
};


template<typename T = std::string>
T MyGlobalMsg{ "OK" };

void useVarTemplates()
{
  auto msg =	MyGlobalMsg<const char*>;

  msg = "hello";
	

 //uto msg2 = MyGlobalMsg<int>;
}


struct MyType
{
	int value;
	MyType(int i) : value{ i } {}

	static MyType max ;
};


inline MyType MyType::max{ 0 };


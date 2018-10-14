#include "tupleget.hpp"
#include <string>
#include "maketuples.hpp"
#include "tupleeq.hpp"
#include <iostream>
#include "tupleio.hpp"

void testTuples()
{
	using namespace std::string_literals;

	Tuple<int, double, const char*> t{ 17, 3.14, "Hello World" };

	const char* p = "hello";
	std::string s = p;

	Tuple<long int, long double, std::string> t2{ t };

	auto tt = makeTuple(500, 7.44, "names"s);

	bool equal = t == t2;

	std::cout << t << std::endl;
}

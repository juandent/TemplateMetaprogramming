#include "stdafx.h"

struct MyStruct
{
// private:
	int i = 0;
	std::string s;
};


MyStruct getStruct()
{
	return MyStruct{ 42, "hello" };
}

template<typename T>
struct Temp
{
	using Type = T;
	static Type* p;
};


auto getArr() -> int(&)[2];

std::array<int,4> getArray()
{
	std::array<int, 4> ar = { 1,2,3,4 };
	return ar;
}

void useMyStruct()
{

	const auto& [a, b, c, d] = getArray();

	// auto& [a, b, c, d] = getArray();    // ERROR (prvalue to non const reference is not allowed)
	
	auto& [o, l] = getArr();

	o += 10;
	
	MyStruct ms;
	auto [n, m] = ms;

	auto [id, val] = getStruct();


	const auto& [k, p] = ms;

	//auto w = Temp< decltype(k)>;

	//k = 14;
	auto kk = ms.i;

	
	MyStruct mmm{ 42, "Jim" };

	auto&& [ss, nn] = mmm;

	ss = 10;
	nn = "John";

	std::string sss = std::move(nn);

	std::cout << "nn = " << nn << std::endl;

	std::cout << "mmm.s = " << mmm.s << std::endl;

}


auto getArr() -> int(&)[2]
{
	int arr[2] = {3,9};
	return arr;
}


#include <functional>

void useSearcher()
{
	std::string in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
		" sed do eiusmod tempor incididunt ut labore pisci et dolore magna aliqua";

	std::string needle = "pisci";

	std::boyer_moore_searcher bmsearcher{ needle.begin(), needle.end() };

	for( auto [beg,end] = bmsearcher(in.begin(), in.end());
		beg != in.end();
		std::tie( beg, end) = bmsearcher(end, in.end()))
	{
		std::cout << "found '" << needle << "' at offset " << beg - in.begin() << "-" << end - in.begin()
			<< std::endl;

		auto start_offset = beg - in.begin();

		auto substr = in.substr(start_offset);
		std::cout << substr << std::endl;
	}	
}



#include "stdafx.h"

template<char...> int operator "" _B7();

int aa = 121_B7;

template<char...cs>
int operator "" _B7()
{
	std::array<char, sizeof...(cs)> chars{ cs... };
	for (char c : chars)
	{
		std::cout << "'" << c << "'";
	}
	std::cout << "\n";
	return 0;
}

void useB7()
{
	auto b = 01.3_B7;
	auto c = 0xFF00_B7;

}
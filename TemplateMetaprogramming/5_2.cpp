#include <iostream>
#include <format>
#include <locale>
#include <string>

void useFormat()
{
	std::locale loc{ "en_US.UTF-8"};

	std::locale::global(loc);

	double val{ 1024.56678 };

	auto str = std::format(loc, "{0}{1:>8.2Lf} {0}{1:>9.2Lf}\n", "$", val);

	std::cout << str; 
}
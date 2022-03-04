#include "stdafx.h"

#include "IntToStr.h"

constexpr void useIntToStr()
{
	constexpr const char* converted = "";
	auto* c = IntToStr::Convert<2034>();
	//std::cout << c << std::endl;
}


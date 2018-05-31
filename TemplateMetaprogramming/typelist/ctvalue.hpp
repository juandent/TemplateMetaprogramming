#pragma once

// compile time value
template<typename T, T Value>
struct CTValue
{
	static constexpr T value = Value;
};


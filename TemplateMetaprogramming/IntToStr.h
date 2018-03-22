#pragma once




template<int i, char* buffer, int N>
struct SetDigit
{
	constexpr static void doIt()
	{
		int digit = i % 10;
		buffer[N] = digit + '0';
		SetDigit<i / 10, buffer, N - 1>::doIt();
	}
};

template<char* buffer, int N>
struct SetDigit<0, buffer, N>
{
	constexpr static void doIt()
	{
		buffer[N] = ' ';
		SetDigit<0, buffer, N - 1>::doIt();
	}
};

template<char* buffer>
struct SetDigit<0, buffer, 0>
{
	constexpr static void doIt()
	{
		buffer[0] = ' ';
	}
};


struct IntToStr
{
	constexpr static std::size_t MAX = 10;
	static inline char buffer[MAX];
	//constexpr static const char* literal = "18";

	template<int i>
	constexpr static char* Convert()
	{
		buffer[MAX - 1] = 0;
		SetDigit<i, buffer, MAX - 2>::doIt();
		return buffer;
	}
};

constexpr const char* const Buffer = IntToStr::buffer;

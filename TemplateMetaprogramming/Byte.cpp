


#include <cstddef>
#include <iostream>
#include <bitset>
#include <limits>
#include <charconv>

std::istream& operator>>(std::istream& strm, std::byte& b)
{
	std::bitset<std::numeric_limits<unsigned char>::digits> bs;
	strm >> bs;

	if( ! strm.fail())
	{
		b = static_cast<std::byte>(bs.to_ulong());
	}
	return strm;
}


void useByte()
{
	using namespace std;


	byte b1{ 0x3F };
	byte b2{ 0b1111'0000 };

	byte b3[4]{ b1,b2, byte{1} };

	if(b1 == b3[0])
	{
		b1 <<= 1;
	}

	cout << to_integer<int>(b1) << endl;


	constexpr const int numDigits = numeric_limits<byte>::digits;

	byte b{ 42 };
	using ByteBitset = bitset<numeric_limits<unsigned char>::digits>;
	unsigned val = to_integer<unsigned>(b);
	cout << ByteBitset{ val } << endl;
	string s = ByteBitset{ to_integer<unsigned>(b) }.to_string();

	int value = 42;
	char str[100];
	to_chars_result res = to_chars(str, str + 99, to_integer<int>(b), 2);

	*res.ptr = '\0';


	byte by;
	cin >> by;
	
	
}

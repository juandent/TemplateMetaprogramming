#include "stdafx.h"

#include "SampleTypes.h"


template<typename T, typename U>
struct Conversion
{
private:
	using Small = char;
	struct Big { Small dummy[2]; };

	static Small Test(const U& u);
	static Big Test(...);
	static T MakeT();

public:
	static constexpr bool exists = sizeof(Test(MakeT())) == sizeof(Small);					// OLD
	static constexpr bool exists2 = sizeof(Test(std::declval<T>())) == sizeof(Small);		// MODERN
	static constexpr bool sameType = false;
};

template<typename T>
struct Conversion<T,T>
{
	static constexpr bool exists2 = true;		// MODERN
	static constexpr bool sameType = true;
};


template<typename U, typename T>
constexpr bool SuperSubClass = Conversion<const T*, const U*>::exists2 && !Conversion<const T*, const void*>::sameType;

void useConversion()
{
	constexpr  bool e = Conversion<double, int>::exists2;
	constexpr  bool e2 = Conversion<char, char*>::exists2;
	constexpr  bool e3 = Conversion<char, char>::sameType;

	constexpr  bool ee = Conversion<const double*, const void*>::exists2;

	constexpr bool e4 = SuperSubClass<Shape, Triangle>;
}



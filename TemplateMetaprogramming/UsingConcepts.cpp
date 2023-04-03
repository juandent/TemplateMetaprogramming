


#include <type_traits>
#include <concepts>

template<typename T>
concept Integral = std::is_integral<T>::value;

template<typename T>
requires Integral<T>
T gcd(T a, T b) {
	if (b == 0) { return a; }
	else {
		return gcd(b, a % b);
	}
};

template<typename T>
requires std::integral<T>
T gcd(T a, T b) {
	if (b == 0) { return a; }
	else {
		return gcd(b, a % b);
	}
};

namespace {
	struct A
	{};
}

void useXXXX()
{
	delete new int[5];
	delete new A[5];
}

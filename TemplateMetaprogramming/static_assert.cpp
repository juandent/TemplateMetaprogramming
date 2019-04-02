#include "stdafx.h"


template <typename T>
void by(T& t)  noexcept(std::is_arithmetic<T>::value)
{
	t++;
	static_assert(std::is_arithmetic<T>::value, "Arithmetic type expected");
}

template <typename T>
void call_by(std::vector<T>& v) noexcept(noexcept(by(*v.begin())))
{
	for (auto x : v)
	{
		by(x);
	}
}
void useCall_by() {
	std::vector<int> another{ 0,2,6,9 };
	call_by(another);
}

#ifdef WANT_TO_TEST_STATIC_ASSERT
void useCall_byFail() {
	std::vector<std::string> another{ "juan", "leslie" };
	call_by(another);
}
#endif


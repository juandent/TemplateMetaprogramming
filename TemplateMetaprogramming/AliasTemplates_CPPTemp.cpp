#include "stdafx.h"

template<typename T>
using AddLValueReferenceT = T & ;


void useAddLValueReference()
{
	using ref = AddLValueReferenceT<int>;
	int i = 4;
	const ref pR = i;
}

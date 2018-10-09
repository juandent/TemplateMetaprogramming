#include "stdafx.h"

#include "typelistSelect.hpp"


using SignedIntegralTypes = Typelist<signed char, short, int, long, long long>;

using ReversedSignedIntegralTypes = Select<SignedIntegralTypes, ValueList<unsigned, 4, 3, 2, 1, 0>>;

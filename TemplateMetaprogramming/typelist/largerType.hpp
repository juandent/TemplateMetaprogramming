#pragma once

#include "..\traits\IfThenElse.hpp"

template<typename T, typename V>
class LargerTypeT : public IfThenElseT< sizeof(T) >= sizeof(V), T, V>
{};


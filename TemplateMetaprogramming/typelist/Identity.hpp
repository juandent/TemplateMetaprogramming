#pragma once

// yield T when using member Type:
template<typename T>
struct IdentityT {
	using Type = T;
};

template<typename T>
using Identity = typename IdentityT<T>::Type;

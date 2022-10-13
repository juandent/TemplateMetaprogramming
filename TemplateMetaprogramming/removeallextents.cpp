#include <type_traits>


template<typename T>
struct RemoveAllExtentsT
{
	using type = T;
};


template<typename T, size_t SZ>
struct RemoveAllExtentsT<T[SZ]>
{
	using type = typename RemoveAllExtentsT<T>::type;
};

template<typename T>
struct RemoveAllExtentsT<T[]>
{
	using type = typename RemoveAllExtentsT<T>::type;
};


template<typename T>
using RemoveAllExtents = typename RemoveAllExtentsT<T>::type;


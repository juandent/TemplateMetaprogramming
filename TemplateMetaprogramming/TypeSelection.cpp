#include "stdafx.h"


template<typename T, bool isPolymorphic>
class NiftyContainerTraits
{
	using ValueType = T*;
};

template<typename T>
class NiftyContainerTraits<T, false>
{
	using ValueType = T;
};



template<typename T, bool isPolymorphic>
class NiftyContainer
{
	using Traits = NiftyContainerTraits<T, isPolymorphic>;
	using ValueType = typename Traits::ValueType;
};

// above does not scale

// extracting type selection to its own class:

template<bool flag, typename T, typename  U>
struct Select				// If
{
	using Result = T;
};

template<typename T, typename U>
struct Select<false, T, U>
{
	using Result = U;
};

template<typename T, bool isPolymorphic>
class NiftyContainer2
{
public:
	using ValueType = typename Select<isPolymorphic, T*, T>::Result;
	void add(ValueType val) { vec.push_back(val); }
	ValueType operator[](int ndx) { return vec[ndx]; }
private:
	std::vector<ValueType> vec;


	
};

#include "SampleTypes.h"

void useNiftyContainerAndSelect()
{
	NiftyContainer2<Shape, true> cont;
	cont.add(new Triangle);

	NiftyContainer2<Triangle, false> cont_val;
	cont_val.add(Triangle{});

}


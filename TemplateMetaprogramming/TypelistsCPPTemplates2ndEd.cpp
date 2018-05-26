//#include "stdafx.h"
#include <type_traits>

#include "traits/IfThenElse.hpp"
#include "typelist/Typelist.hpp"
#include "typelist/IsEmpty.hpp"
#include "typelist/typelistFront.hpp"
#include "typelist/typelistPopFront.hpp"
#include "typelist/typelistPushFront.hpp"
#include "typelist/typelistNthElement.hpp"
#include "typelist/typelistLargestType.hpp"
#include "typelist/typelistGenericLargestType.hpp"
#include "typelist/typelistPushBack.hpp"
//#include "typelist/typelistGenericPushBack.hpp"

// Sample

using SignedIntegralTypes = Typelist<signed char, short, int, long, long long>;


// sample:

constexpr bool same = std::is_same< PopFront<SignedIntegralTypes>, Typelist<short, int, long, long long>>::value;

static_assert(same == true);


// sample

constexpr bool push_front_same = std::is_same< PushFront<SignedIntegralTypes,bool>, Typelist<bool, signed char, short, int, long, long long>>::value;

static_assert(push_front_same == true);


using lowlevelLargest = LowLevel::LargestType<SignedIntegralTypes>;

using highlevelLargest = HighLevel::LargestType<SignedIntegralTypes>;

constexpr bool same_largest = std::is_same<lowlevelLargest, highlevelLargest>::value;

static_assert(same_largest);

#include "typelist/typelistGenericPushBack.hpp"



using integers = PushBackRec<Typelist<short, int>, long>;

constexpr bool push_back_rec = std::is_same<Typelist<short, int, long>, integers>::value;

#include "typelist/typelistReverse.hpp"


using straight = Typelist<char, int, long>;

using inverted = Reverse<straight>;

constexpr bool reversed = std::is_same<inverted, Typelist<long, int, char>>::value;


#include "typelist/typelistPopBack.hpp"

using poppedBack = PopBack<straight>;

constexpr bool popped_back = std::is_same<poppedBack, Typelist<char, int>>::value;

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


#include "typelist/transform.hpp"
#include "typelist/addconst.hpp"

using const_straight = Transform<straight, AddConstT>;

constexpr bool transformed_ok = std::is_same<const_straight, Typelist<const char, const int, const long>>::value;

#include "typelist/accumulate.hpp"

using result = Accumulate<Typelist<int, char>, PushFrontT, Typelist<>>;


using reversed_accum = Reverse_via_accumulate<Typelist<int,char>>;

constexpr bool reversed_accum_ok = std::is_same<reversed_accum, Typelist<char, int>>::value;


#include "typelist/largesttypeaccum0.hpp"

using types = Typelist<bool, char, double, long double, long long>;

using largest = LargestTypeAcc<types>;

#include "typelist/largesttypeacc.hpp"

using largest_accum = LargestTypeAccOkNull<types>;
//using largest_accum_null_list = LargestTypeAccOkNull<Typelist<>>;


void testAccumulate()
{
	auto ld = sizeof(long double);
	auto ll = sizeof(long long);
	result* p = nullptr;
	reversed_accum* pp = nullptr;
	largest* l = nullptr;
	largest_accum* la = nullptr;
}

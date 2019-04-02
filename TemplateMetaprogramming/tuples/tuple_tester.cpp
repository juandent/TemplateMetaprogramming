#include "stdafx.h"

#include "pushfront.hpp"
#include "pushback.hpp"
#include "popfront.hpp"
#include "popback.hpp"

using namespace std::string_literals;

void useTuplePushfront()
{
	Tuple<int, std::string> t( 50, "juan"s );
	auto tres = pushFront(t, 57.77);

	auto tback = pushBack(t, true);

	auto tpop = popFront(t);

	using fr = typename FrenteT<Tuple<int, double>>::Type;

	using rev = Reverse<Tuple<int, bool,char>>;
	rev* pRev;

	using pback = PopBack<Tuple<int, bool, char>>;

	auto pbackTuple = popBack(tback);

}
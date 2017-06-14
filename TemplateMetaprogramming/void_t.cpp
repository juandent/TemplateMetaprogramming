#include "stdafx.h"

#include <type_traits>

using namespace std;



struct Experiment
{
	//Experiment& operator&() = delete;
};

Experiment* operator&(Experiment& exp)
{
	return &exp;
}

#define SFINAE_DETECT(name, expr)                                       \
  template <typename T>                                                 \
  using name##_t = decltype(expr);                                      \
  template <typename T, typename = void>                                \
  struct has_##name : public std::false_type {};                        \
  template <typename T>                                                 \
  struct has_##name<T, void_t<name##_t<T>>> : public std::true_type {};


SFINAE_DETECT(address_operator, declval<T&>().operator&())

static const bool _hasAddressOperator = has_address_operator<Experiment>::value;

SFINAE_DETECT(can_take_address, &declval<T&>())

static const bool _canTakeAddress = has_can_take_address<Experiment>::value;

SFINAE_DETECT(address_via_free_function, operator&(declval<T&>()))

static const bool _addressViaFreeFunc = has_address_via_free_function<Experiment>::value;


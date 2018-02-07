#include "stdafx.h"

#include <type_traits>

#if 1
using namespace std;



struct Experiment
{
	//Experiment& operator&() = delete;
};

Experiment* operator&(Experiment& exp)
{
	return nullptr;
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

#undef SFINAE_DETECT


/////////////////////////////////////////////////////////////////////////////////////////////////

//////////// CPP Templates 2nd edition

// pg. 133

template<typename T>
auto len(T const& t) -> decltype((void)(t.size(int{})), (void)(t.top), T::size_type())			// returns T::size_type, requires t.size()
{
	return t.size(5);
}

struct AA
{
	int top;
	int m;
	using size_type = std::size_t;
	size_type size() const   { return sizeof(int); }
	size_type size(int a) const  { return a*sizeof(int); }

	AA& operator,(AA const& other)
	{
		top += other.top;
		m += other.m;
		return *this;
	}
};

void useRestrictionOnReturnType()
{
	AA anA{ 54, 10 };
	std::cout << len(anA) << std::endl;

	AA other{ 66, 20 };
	anA,other;
}


#endif

template<typename T, typename = std::void_t<>>
struct HasBeginT : std::false_type
{};

template<typename T>
struct HasBeginT< T, std::void_t<decltype(std::declval<T>().shoot())>> : std::true_type
{};


void useHasBegin()
{
	vector<int> v{ 1,2,3,4,5 };
	auto it = v.begin();

	using t = HasBeginT<vector<int>>::type;
	auto ok = t::value;
}



// primary template:
template<typename, typename, typename = std::void_t<>>
struct HasLessT : std::false_type
{
};

// partial specialization (may be SFINAE'd away):
template<typename T1, typename T2>
struct HasLessT < T1, T2, std::void_t<decltype(std::declval<T1>() < std::declval<T2>()) >>
	: std::true_type
{
};

void useHasLess()
{

}

namespace creativeUseOfOperatorComma
{

	template<typename T>
	struct vector_maker
	{
		std::vector<T> vec;
		vector_maker& operator,(T const& rhs) {
			vec.push_back(rhs);
			return *this;
		}

		std::vector<T> finalize() {
			return std::move(vec);
		}
	};

	void main() {
		auto a = (vector_maker<int>(), 1, 2, 3, 4, 5).finalize();
	}

}

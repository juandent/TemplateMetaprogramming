#include "stdafx.h"

#include <type_traits>  // for true_type and false_type
#include <utility>      // for declval

template<typename FROM, typename TO>
struct IsConvertibleHelper {
private:
	// test() trying to call the helper aux(TO) for a FROM passed as F:
	static void aux(TO);
	template<typename F, typename = decltype(aux(std::declval<F>()))>
	static std::true_type test(void*);
	// test() fallback:
	template<typename>
	static std::false_type test(...);
public:
	using Type = decltype(test<FROM>(nullptr));
	static constexpr bool value = Type::value;
};

template<typename FROM, typename TO>
struct IsConvertibleT : IsConvertibleHelper<FROM, TO> {
};

template<typename FROM, typename TO>
using IsConvertible = typename IsConvertibleT<FROM, TO>::Type;

template<typename FROM, typename TO>
constexpr bool isConvertible = IsConvertibleT<FROM, TO>::value;


struct Person
{

};

struct Student : Person
{
};


void useConvertible()
{
	using isT = IsConvertible<int, long>;
	isT* pisT;
	bool is = isConvertible<int, long>;
	bool ischar = isConvertible<long, char>;
	Person p;
	Student s;

	bool s_is_a_p = isConvertible<Student, Person>;
	bool p_is_a_s = isConvertible<Person, Student>;
}
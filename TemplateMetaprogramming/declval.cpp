#include "stdafx.h"

using namespace std;

using array_type = char[30];
using function_type = int();
struct class_type { virtual int mem_fun() = 0; };

/*
// these declarations are errors: a function can't return a value of a non-copyable type

array_type foo_a() ; // *** error: function can't return an array (by value)
function_type foo_f() ; // *** error: function can't return a function (by value)
class_type foo_c() ; // *** error: function can't return an abstract type (by value)
*/

// these declarations are fine: a function can return a reference to any referenceable type
//#define JDH
#ifdef JDH
array_type&& bar_a();
function_type&& bar_f(); // fine
class_type&& bar_c(); // fine
#else
array_type&& bar_a(); // fine
function_type&& bar_f(); // fine
class_type&& bar_c(); // fine
#endif

void useDeclVal()
{
	std::cout << sizeof(bar_a()) << ' ' << sizeof(bar_a()[5]) << '\n' // 30 1
		<< sizeof(std::declval<array_type>()) << ' ' << sizeof(std::declval<array_type>()[5]) << '\n'; // 30 1

   /*
   // these are errors: strawman functions can only be used in unevaluated contexts
   auto&& bad = bar_a() ; // *** error: bar_a is not defined
   auto&& also_bad = std::declval<array_type>() ; // *** error: std::declval<T> is not defined
   */
}




template < typename T > using type_of_declval = decltype(std::declval<T>());

template < typename T > struct print_type;
template <> struct print_type<int&> { print_type() { std::cout << "lvalue reference to int\n"; } };
template <> struct print_type<const int&> { print_type() { std::cout << "lvalue reference to const int\n"; } };
template <> struct print_type<int&&> { print_type() { std::cout << "rvalue reference to int\n"; } };

void whyRValueInsteadOfLvalue()
{
	print_type< type_of_declval<int> > {}; // rvalue reference to int ie. int&&

	print_type< type_of_declval<int&> > {}; // lvalue reference to int ie. int&

	print_type< type_of_declval<const int&> > {}; // lvalue reference to const int ie. const int&

	print_type< type_of_declval<int&&> > {}; // rvalue reference to int ie. int&&

											 // sizeof( &std::declval<int>() ) ; // *** error: can't take address of an rvalue
											 // sizeof( &std::declval<int&&>() ) ; // *** error: can't take address of an rvalue

											 // these are fine: take address of lvalue (result of std::declval in unevaluated contexts)
	std::cout << sizeof(&std::declval<int&>()) << '\n'; // sizeof( int* )
	std::cout << sizeof(&std::declval<const int&>()) << '\n'; // sizeof( const int* )

}



////////////////////////////////////////////////////////////
//traits/isvalid.hpp


// helper: checking validity of f(args...) for F {f} and Args... args:
template<typename F, typename... Args, typename = decltype(std::declval<F>()(std::declval<Args&&>()...))>
std::true_type  isValidImpl(void*);

// fallback if helper SFINAE'd out:
template<typename F, typename... Args>
std::false_type isValidImpl(...);

// define a lambda that takes a lambda f and returns whether calling f with args is valid
inline constexpr
auto isValid = [](auto f) {
	return [f](auto&&... args) {
		return decltype(isValidImpl<decltype(f), decltype(args) && ...>(nullptr)){};
	};
};

// helper template to represent a type as a value
template<typename T>
struct TypeT {
	using Type = T;
};

// helper to wrap a type as a value
template<typename T>
constexpr auto type = TypeT<T>{};

// helper to unwrap a wrapped type in unevaluated contexts
template<typename T>
T valueT(TypeT<T>);  // no definition needed


inline /*constexpr*/
auto execute = [](auto f) {
	return [=](auto&&... args) {
		return f(args...);
	};
};

auto ti = type<int>;
using decldecl = decltype(decltype(valueT(ti))());

class ContainsFirst
{
public:
	void first() {}
};

void useLambdaInLambda()
{
	decldecl* pDcl;

	auto isDefaultConstructible = isValid([](auto x)-> decltype((void)decltype(valueT(x))()) {});

	auto r1 = isDefaultConstructible(type<int>);
	auto r2 = isDefaultConstructible(type<int&>);


	auto hasFirst = isValid([](auto x) -> decltype((void)valueT(x).first) {});

	auto r3 = hasFirst(type<int>);
	auto r4 = hasFirst(type<ContainsFirst>);

	// internal lambda
	auto duplicate = [](int a, long b) { return 2 * a + b; };
	auto tmp = isValid(duplicate);
	auto res = tmp(5, 10).value;
	auto r = execute(duplicate)(5, 10L);
}



void callDeclVal(int* p = nullptr)
{
	using type = decltype(std::declval<int&>());
	int j = 9;
	type pp = j;
}


void useCompileTimeIf()
{
	using T = int;

	if constexpr (std::is_same_v< decltype(std::declval<T>()), T >)
		std::cout << "type of std::declval<T>() is T\n";
	else
		std::cout << "type of std::declval<T>() is not T\n";
}


// 19.6.4 Using Generic Lambdas to Detect Members
// pg.438
//define to check for data member first

void detectMembersViaGenericLambdas()
{
	// helper to unwrap a wrapped type in unevaluated contexts
	//template<typename T>
	//T valueT(TypeT<T>);
	constexpr auto hasFirst = isValid([](auto x) -> decltype((void)valueT(x).first) {});
	
	// helper to wrap a type as a value
	//template<typename T>
	//constexpr auto type = TypeT<T>{};
	cout << "hasFirst " << hasFirst(type<pair<int, int>>) << endl;

	// define to check for member type size_type:
	constexpr auto hasTypeSize = isValid([](auto x)-> decltype(typename std::decay_t< decltype(valueT(x))>::size_type()) {});
	//constexpr auto hasTypeSize = isValid([](auto x)-> typename std::decay_t< decltype(valueT(x))>::size_type {});


	struct CX
	{
		using size_type = std::size_t;
	};

	cout << "hasSizeType: " << hasTypeSize(type<CX&>) << endl;

	if constexpr(!hasTypeSize(type<int>))
	{
		cout << "int has no size-type\n";
	}

	// define to check for <
	constexpr auto hasLess = isValid([](auto x, auto y) -> decltype(valueT(x) < valueT(y)) {});

	cout << "hasLess: " << hasLess(type<int>, type<char>) << endl;
	cout << "hasLess: " << hasLess(type<string>, type<string>) << endl;
	cout << "hasLess: " << hasLess(type<string>, type<int>) << endl;
	cout << "hasLess: " << hasLess(type<string>, type<decltype("Hello")>) << endl;


}

namespace GenericSyntax
{
	constexpr auto hasFirst = isValid([](auto&& x) -> decltype(&x.first) {});
	template<typename T>
	using HasFirstT = decltype(hasFirst(declval<T>()));

//	constexpr auto hasSizeType = isValid([](auto&& x) -> typename decay_t<decltype(x)>::size_type {});
	constexpr auto hasSizeType = isValid([](auto&& x) -> decltype(typename decay_t<decltype(x)>::size_type()) {});

	template<typename T>
	using HasSizeT = decltype(hasSizeType(declval<T>()));

	constexpr auto hasLess = isValid([](auto&& x, auto&& y) -> decltype(x < y) {});
	template<typename T, typename U>
	using HasLessT = decltype(hasLess(declval<T>(), declval<U>()));



	void detectMembersViaGenericLambdas()
	{

		cout << "first: " << HasFirstT<pair<int, int>>::value << endl;

		struct CX
		{
			using size_type = size_t;
		};

		cout << "size_type: " << HasSizeT<CX>::value << endl;
		cout << "size_type: " << HasSizeT<int>::value << endl;

		cout << HasLessT<int, char>::value << endl;
		cout << HasLessT<string, string>::value << endl;
		cout << HasLessT<string, int>::value << endl;
		cout << HasLessT<string, char*>::value << endl;


	}
}

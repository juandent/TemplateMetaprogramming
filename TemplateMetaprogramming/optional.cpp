#include "stdafx.h"



#include <numeric>
#include <optional>

namespace std
{
	template<class Arg1, class Arg2, class Result>
	struct binary_function
	{
		using first_argument_type = Arg1;
		using second_argument_type = Arg2;
	};
}

#include <functional>

#include <boost/optional.hpp>

using namespace std;



optional<int> asInt(const string& s)
{
	try
	{
		return stoi(s);
	}
	catch(...)
	{
		return std::nullopt;
	}
}


optional<int> asInt2(const string& s)
{
	optional<int> ret;	// initially empty
	try
	{
		ret = stoi(s);
	}
	catch (...)
	{}
	return ret;
}

void useOptAsInt()
{
	for (auto a : { "42","  077","hello", "0x33" })
	{
		optional<int> oi = asInt(a);
		if(oi)
		{
			cout << "convert " << a << " to int: "  << *oi << endl;
		}
		else
		{
			cout << "cannot convert " << a << " to int" << endl;
		}
	}
}


// optionals as members

class Name
{
	string first;
	optional<string> middle;
	string last;
public:
	Name( string f, optional<string> m, string l)
		: first(move(f)), middle{move(m)}, last{move(l)}
	{}

	friend ostream& operator<<( ostream& os, const Name& name)
	{
		os << name.first << (name.middle ? *name.middle : "") << name.last << endl;
		return os;
	}
};

void useOptionals()
{
	string f = "Juan";
	string g = "Dent";

	Name name{ f,nullopt, g };
	Name n{ "juan", nullopt, "dent" };
}


bool pred(int x)
{
	return x == 0;
}

bool allNonZero( std::initializer_list<int> xs)
{
	return std::find_if(xs.begin(), xs.end(), 	[](int x) {return x == 0; }) == xs.end();
}


template<typename ...Counts>
bool allNonZero(Counts ... counts)
{
	static_assert((std::is_same_v<Counts, int> && ...));
	return (counts && ...);
}

void useAllNonZero()
{
	auto are = allNonZero(2, 1, 8, 0);
	
}

template< typename ...Counts>
bool allNonZero(Counts ...xs) requires (std::is_same_v<Counts, int> && ...)
{
	return (xs && ...);
}


template<typename T>
concept Hashable = requires(T a)
{
	{ std::hash<T>{}(a)} -> std::convertible_to<std::size_t>;
};



// CONCEPT convertible_to
template <class _From, class _To>
concept convertible_to = __is_convertible_to(_From, _To)
&& requires(add_rvalue_reference_t<_From>(&_Fn)())
{
	static_cast<_To>(_Fn());
};


template <class T, class U>
concept Derived = std::is_base_of<U, T>::value;


struct Rectangle {};

struct Square : Rectangle {};

template<typename T, typename U> requires (Derived<T,U>)
void useDerived(T& t, U& u)
{
	u = t;
}


#if 0
template<Derived T, U>
void useDerived(T& t, U& u)
{
	u = t;
}
#endif

void use()
{
	Square sq;
	Rectangle rc;
	useDerived(sq, rc);


	int x = 0;

	decltype(auto) m =(x + 1);

	decltype((x + 1)) ss;
}

template<typename T>
concept Incrementable = requires (T x) { x++; ++x; };

template<typename T>
concept Decrementable = requires (T x) { x--; --x; };

template<Incrementable T>
void f(T) requires Decrementable<T>;

template<Incrementable T>
void f(T) requires Decrementable<T>; // OK, redeclaration

template<typename T>
requires Incrementable<T>&& Decrementable<T>
void f(T); // Ill-formed, no diagnostic required


template<Incrementable T>
void g(T) requires Decrementable<T>;

template<Decrementable T>
void g(T) requires Incrementable<T>;


template <class T, class U>
concept SubClass = std::is_base_of<U, T>::value;


struct ABase
{
	ABase() = default;
};
struct ASubBase : ABase
{
	ASubBase() = default;
};
struct AAnother
{
};

template<SubClass<ABase> T>
void f(T);  // T is constrained by SubClass<T, ABase>



void useSubBase()
{
	// ASubBase s;
	AAnother a;
	// f(s);
	// f(a);
}


template<class T> constexpr bool is_meowable = true;
template<class T> constexpr bool is_cat = true;

template<class T>
concept Meowable = is_meowable<T>;

template<class T>
concept BadMeowableCat = is_meowable<T> && is_cat<T>;

template<class T>
concept GoodMeowableCat = Meowable<T> && is_cat<T>;

template<Meowable T>
void f1(T); // #1

template<BadMeowableCat T>
void f1(T); // #2

template<Meowable T>
void f2(T); // #3

template<GoodMeowableCat T>
void f2(T) {} // #4

void g() {
	// f1(0); // error, ambiguous:
		   // the is_meowable<T> in Meowable and BadMeowableCat forms distinct
		   // atomic constraints that are not identical (and so do not subsume each other)

	f2(0); // OK, calls #4, more constrained than #3
		   // GoodMeowableCat got its is_meowable<T> from Meowable
}







// template<class T, class ...Args>
// concept constructible_from = (T t, Args...);


#include <type_traits>

namespace InverseOrderConcepts
{

	/// Concept in order to deduce if sth. is base of sth else
	template <typename Impl, typename Base>             //XXX: here the order of Impl and Base are not 
	concept Implements = std::is_base_of_v<std::remove_reference_t<Base>, // what I would've expected.
		std::remove_reference_t<Impl>>;
	/// Example Base class impl
	struct BaseExample {};
	/// Implementation of BaseExample
	struct ImplExample : BaseExample {};

	/// Function in which the concept is applied
	template <Implements<BaseExample>... Baes> void f(Baes &&...) {}//} ((void)b, ...); }

	void main() {
		(void)std::is_base_of_v<BaseExample, std::remove_reference_t<ImplExample&&>>; //< true
		(void)std::is_base_of_v<BaseExample, std::remove_reference_t<ImplExample&>>;  //< true
		f(ImplExample{}, ImplExample{});
	}


	template<typename Derived, typename Top>
	concept Sub = std::is_base_of<Top, Derived>::value;
	
	/// <summary>
	/// OJO
	/// </summary>
	template<Sub<BaseExample> X>
	struct WorkIn
	{};
	// is short for
	template<class X> requires Sub<X, BaseExample>
	struct WorkInOther
	{};

	template<>
	struct WorkInOther<ImplExample>
	{};


	template<auto n>
	struct BB {};

	BB<3> b;
	BB<'a'> c;


	struct A { friend bool operator==(const A&, const A&) = default; };
	template<A a> void h() {
		&a; // OK
		const A& ra = a, & rb = a; // Both bound to the same template parameter object
		assert(&ra == &rb); // passes
	}

	void call_h()
	{
		constexpr static A anA;
		h<anA>();
		
	}
}


template<auto N> constexpr auto val = N;


auto v1 = val<10>;		// int
auto v2 = val<true>;	// bool
auto v3 = val<'a'>;			// char

template<decltype(auto) N>
struct SN
{
	using Type = decltype(N);
	void printN() const
	{
		std::cout << "N: " << N << '\n';
	}
};


void useVariableTemplates()
{
	static const int c = 42;
	static int v = 42;

	SN<c> s1;

	SN<(v)>::Type;
	
	SN<(c)> s2;
	s1.printN();
	s2.printN();
	SN<(v)> s3;
	v = 77;
	s3.printN();
}


template<typename T> concept C1 = true;
template<typename... Ts> concept C2 = true; // variadic concept
template<typename T, typename U> concept C3 = true;

template<C1 T> struct s1;         // constraint-expression is C1<T>
template<C1... T> struct s2;      // constraint-expression is (C1<T> && ...)
template<C2... T> struct s3;      // constraint-expression is (C2<T> && ...)
template<C3<int> T> struct s4;    // constraint-expression is C3<T, int>
template<C3<int>... T> struct s5; // constraint-expression is (C3<T, int> && ...)




template<typename T>
concept Addable = requires (T x) { x + x; }; // requires-expression

template<typename T> requires Addable<T> // requires-clause, not requires-expression
T add(T a, T b) { return a + b; }

template<typename T>
requires requires (T x) { x + x; } // ad-hoc constraint, note keyword used twice
T add(T a, T b) { return a + b; }

template<class T>
concept WRONG = requires
{
	new int[-(int)sizeof(T)]; // invalid for every T: ill-formed, no diagnostic required
};

template<typename T> requires WRONG<T> // requires-clause, not requires-expression
T add(T a, T b) { return a + b; }


template<typename T> requires requires (T x) { x + x; }
struct S
{};

template<typename T> requires requires (T x) { x + x; }
struct MM
{};


template<typename T> using Ref = T&;
template<typename T> concept C =
requires {
	typename T::inner; // required nested member name
	typename S<T>;     // required class template specialization
	typename Ref<T>;   // required alias template substitution
};


template<typename T> requires C<T>
struct SS
{};

struct M
{
	struct inner {};
	friend int operator+( M& a, M& b)
	{
		return 1;
	}
};

void nestedMember()
{
	// SS<int> a;	// wrong int has no nested inner
	SS<M> a;
}


template <class T, class U> using CommonType = std::common_type_t<T, U>;
template <class T, class U> concept Common =
requires (T t, U u)
{
	typename CommonType<T, U>; // CommonType<T, U> is valid and names a type
	{ CommonType<T, U>{std::forward<T>(t)} };
	{ CommonType<T, U>{std::forward<U>(u)} };
};


struct Base
{
	Base(const Base&) = delete; // default;
	Base(Base&&) = default;
	
	
	template<typename T>
	Base(std::initializer_list<T> list) {}
};

struct Der : Base
{
	
};

using ApplyCommon = CommonType<Base, Der>;

template <class T, class U> requires Common<T, U>
	CommonType<T, U> test(T t, U u)
	{
		auto r = CommonType<T, U>{ std::forward<T>(t) };
		return r;
	}

void useCommonType(Base b, Der d)
{
	CommonType<Base, Der>{std::forward<Base>(b)};
	CommonType<Base, Der>{std::forward<Der>(d)};
	Base{ std::forward<Base>(b) };

}

template <class T, class U> requires Common<T,U>
CommonType<T,U> add(T t, U u )
{
	auto r = CommonType<T, U>{ std::forward<T>(t)};			// long { T&& t};
	return t + u;
}


template <class _Ty>
constexpr _Ty&& forw(remove_reference_t<_Ty>& _Arg) noexcept { // forward an lvalue as either an lvalue or an rvalue
	return static_cast<_Ty&&>(_Arg);
}

template <class _Ty>
constexpr _Ty&& forwa(remove_reference_t<_Ty>&& _Arg) noexcept { // forward an rvalue as an rvalue
	static_assert(!is_lvalue_reference_v<_Ty>, "bad forward call");
	return static_cast<_Ty&&>(_Arg);
}

template <class _Ty>
constexpr _Ty&& forw(_Ty&& _Arg) noexcept { // forward an rvalue as an rvalue
	static_assert(!is_lvalue_reference_v<_Ty>, "bad forward call");
	return static_cast<_Ty&&>(_Arg);
}

void useCommon()
{
	int a = 4;
	int& b = a;
	
	auto res = add(b, 8L);

	decltype(auto) xx = forw<int>(b);

	int&& n = 5;
	constexpr auto exp = std::same_as<decltype((n + 1)),int>;

	
	
}







// template<class T>
// constexpr bool is_meowable = true;

template<class T>
constexpr bool is_purrable() { return true; }

template<class T>
void f(T) requires is_meowable<T>; // OK

// template<class T>
// void g(T) requires is_purrable<T>(); // error, is_purrable<T>() is not a primary expression

template<class T>
void h(T) requires (is_purrable<T>()); // OK



// #define __cpp_lib_concepts
#include <concepts>


// template<typename T>
// concept Incrementable = requires (T a) { ++a; a++; };

template<typename T>
concept EqualityComparable = requires (T a, T b) { a == b; };


// short form
// void g1(std::equality_comparable<int>* first, 
	// Incrementable&);
// long form:
  // template<EqualityComparable T, Incrementable U> void g1(const T*, U&);
// longer form:
template<typename T, typename U>
void g11(const T*, U&) requires EqualityComparable<T> && Incrementable<U>;

// void f2(std::vector<auto*>...);

template<typename... T>
void f2(std::vector<T*>...);

// void f4(auto (auto::*)(auto));
template<typename T, typename U, typename V> void f4(T (U::*)(V));


struct MMM
{
	friend bool operator==(MMM&, MMM&) { return true; }
	MMM& operator ++() { return *this; }
};

template<std::integral T>    // requires std::integral<T>
bool is_power_of_2(T i)
{
	return i > 0 && (i & (i - 1)) == 0;
}

template<std::floating_point T>     // requires std::floating_point<T>
	bool is_power_of_2(T x)
	{
		int exponent;
		const T mantissa = std::frexp(x, &exponent);
		return mantissa == T(0.5);
	}

#include <concepts>

template<typename T>
concept my_number = ( std::integral<T> || std::floating_point<T> ) && sizeof(T) <= 8;

// auto f(my_number x)
// {
// 	
// }

template<typename T>
concept hashable = requires(T t, T u)
{
	{std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
	{ t = u };
	{ T{ t }  };
	{ t.x } -> std::convertible_to<int> ;
	{ t.print() };
};

struct Small
{
	int x;
	Small(const Small& s) = default; // delete;
	Small& operator=(const Small& s) = default;
	void print() {}
};

template<>
struct std::hash<Small>
{
	size_t operator()(Small s)
	{
		return 1000;
	}
};

template<hashable T>
class hash_map
{
	
};

hash_map<Small> m;

std::optional<std::string> getString()
{
	std::string str{ "dddd" };
	return str;
}


#include <ranges>
#include <algorithm>


template<typename T>
struct Wrapper
{
	T&& t;
	Wrapper(T&& t) : t{std::move(t)} {}

	// Wrapper(T&& t) : t{ t } {}
	
	operator T&()
	{
		return t;
	}

	Wrapper(const Wrapper& other) : t{ std::move(other.t) }
	{
	}
	Wrapper( Wrapper&& other) : t{ std::move(other.t)}
	{
	}
	Wrapper& operator=(const Wrapper& other)
	{
		t = std::move(other.t);
		return *this;
	}
	Wrapper& operator=(Wrapper&& other)
	{
		t = std::move(other.t);
		return *this;
	}

};

struct User
{
	User(const std::string& name, const int age)
		: name(name),
		  age(age)
	{
	}

	std::string name;
	int age;
	
	User(const User& usr) = delete;
	
	User(User&& usr)
	{
		name = std::move(usr.name);
		age = usr.age;
	}
	User& operator=(const User& usr) = delete;
	User& operator=(User&& usr)
	{
		name = std::move(usr.name);
		age = usr.age;
		return *this;
	}
};

std::optional<User> getUser()
{
	User u{ "juan", 60 };
	return u;
}

User getDirUser()
{
	return { "juan", 60 };
}

bool underage(const User& user)
{
	return user.age < 18;
}

void useConcepts()
{
	std::optional<bool> ob{ false };
	if( ob)
	{
		auto x = *ob;

		if( ob == false)
		{
			int x = 0;
		}
	}
	if( !ob)
	{
		int x = 0;
	}
	
	boost::optional u{ User{ "juan", 60 } };
	if(u)
	{
		u->name;
		u->age;
	}
	// std::optional<User> uu{ std::in_place, "juan", 60 };
#if 0
	std::optional u{ getDirUser() };
	auto yy = getUser().value_or(User{"empty",0});
	auto zz = getUser().value();
#endif
#if 0	
	// Wrapper<User> wu(User{ "james", 56 });
	std::optional w{ Wrapper<User>(User{"james", 56}) };
	if (w)
	{
		auto s = w->t.name;
		auto a = w->t.age;
		// User user = (*w);
	}
#endif
	auto y = getString();
	const auto& r1 = getString().value();	// Error
	auto&& r2 = getString().value();				// Error
	
#if 1	
	int a = 4;
	int b = 'a';
	MMM mmm;
	// g1(&mmm, b);
	const std::vector<User> users = { {"juan", 60},{"roberto", 58},{"leslie", 2} };
	std::vector<User> filtered;

	copy_if(users.begin(), users.end(), back_inserter(filtered), std::not_fn(underage));

	transform(filtered.begin(), filtered.end(), ostream_iterator<int>(cout, "\n"), [](const auto& user)
		{
			return user.age;
		});
	
	// std::ranges::sort(vec, std::less{}, &User::age);


	auto result = users
		| std::views::filter(std::not_fn(underage))
		| std::views::transform([](const auto& user)
			{
				return user.age;
			});



#if 1
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, "\n"));
#else
	std::ranges::copy(result, 
		ostream_iterator<int>(cout, "\n"));
#endif

	std::vector<int> increasing(10);
	iota(increasing.begin(), increasing.end(), 1);
	for(int i : increasing)
	{
		cout << i << endl;
	}
#endif	
}


template<std::semiregular T>
// Credit Alexander Stepanov
// concepts are requirements on T
// Requirement on T: T is semiregular
// T a(b); or T a = b; => copy constructor
// T a; => default constructor
// a = b; => assignment
struct Single {
	T value;
	// Aggregation initialization for Single behaves like following constructor:
	// explicit Single(const T& x) : value(x){}

	// Implicitly declared special member functions behave like following definitions,
	// except that they may have additional properties:
	// Single(const Single& x) : value(x.value){}
	// Single(){}
	// ~Single(){}
	// Single& operator=(const Single& x) { value = x.value; return *this; }
	// comparison operator is not defined; it is not required by `semiregular` concept
	// bool operator== (Single const& other) const = delete;
};

template<std::semiregular T>
void print(T x) // <- note `semiregular` in the signature
{
	std::cout << x.value << ' ';
}

void samplefn()
{
	Single<int> myInt1{ 4 };      // aggregate initialization: myInt1.value = 4
	Single<int> myInt2(myInt1); // copy constructor
	Single<int> myInt3;         // default constructor
	myInt3 = myInt2;            // copy assignment operator
//  myInt1 == myInt2;           // Error: operator== is not defined

	print(myInt1); // ok: Single<int> is a `semiregular` type
	print(myInt2);
	print(myInt3);

}


// #include <concepts>

// namespace ranges = std::ranges;
// using namespace std::ranges;


template < class T, class U >
concept CommonReference =
std::is_same_v<std::common_reference_t<T, U>, std::common_reference_t<U, T>> &&
std::is_convertible_v<T, std::common_reference_t<T, U>> &&
std::is_convertible_v<U, std::common_reference_t<T, U>>;



template< class T, class U >
concept SwappableWith =
CommonReference<
	const std::remove_reference_t<T>&,
	const std::remove_reference_t<U>&> &&
	requires(T && t, U && u) {
	ranges::swap(std::forward<T>(t), std::forward<T>(t));
	ranges::swap(std::forward<U>(u), std::forward<U>(u));
	ranges::swap(std::forward<T>(t), std::forward<U>(u));
	ranges::swap(std::forward<U>(u), std::forward<T>(t));
};

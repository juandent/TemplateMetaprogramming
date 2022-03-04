#include <compare>
#include <string>
#include <vector>
#include <iostream>
#include <typeindex>

struct MyInt {
	int value;
	explicit MyInt(int val) : value{ val } { }
	constexpr auto operator<=>(const MyInt & rhs) const {
		 return value <=> rhs.value;
	}
};

template<typename T>
std::strong_ordering operator<=>( const T& l, const T& r)
{
	if (l < r)
		return std::strong_ordering::less;
	if (l == r)
		return std::strong_ordering::equal;
	else
		return std::strong_ordering::greater;
}

void useSpaceshipOperator()
{
	using namespace std::string_literals;
	
	const char* p1 = "Hello";
	std::string m1{ "Hello"s };
	std::string m2{ "World"s };

	auto res = m1 <=> m2;
	
}
#if 1
void useSpaceship()
{
	int a(2011);
	int b(2014);
	auto res = a <=> b;
	if (res < 0) std::cout << "a < b" << '\n';
	else if (res == 0) std::cout << "a == b" << '\n';
	else if (res > 0) std::cout << "a > b" << '\n';

	std::string str1("2014");
	std::string str2("2011");
	auto res2 = str1 <=> str2;
	if (res2 < 0) std::cout << "str1 < str2" << '\n';
	else if (res2 == 0) std::cout << "str1 == str2" << '\n';
	else if (res2 > 0) std::cout << "str1 > str2" << '\n';

	std::vector<int> vec1{ 1, 2, 3 };
	std::vector<int> vec2{ 1, 2, 3 };
	auto res3 = vec1 <=> vec2;
	if (res3 < 0) std::cout << "vec1 < vec2" << '\n';
	else if (res3 == 0) std::cout << "vec1 == vec2" << '\n';
	else if (res3 > 0) std::cout << "vec1 > vec2" << '\n';
}
#endif


#include <compare>
#include <iostream>

// struct MyInt {
// 	int value;
// 	explicit MyInt(int val) : value{ val } { }
// 	auto operator<=>(const MyInt& rhs) const {
// 		return value <=> rhs.value;
// 	}
// };

struct MyDouble {
	double value;
	explicit constexpr MyDouble(double val) : value{ val } { }
	auto operator<=>(const MyDouble&) const = default;
};

template <typename T>
constexpr bool isLessThan(const T& lhs, const T& rhs) {
	return lhs < rhs;
}

void useThreeWay() {

	std::cout << std::boolalpha << '\n';

	MyInt myInt1(2011);
	MyInt myInt2(2014);

	std::cout << "isLessThan(myInt1, myInt2): "
		<< isLessThan(myInt1, myInt2) << '\n';

	constexpr double d1{ 2011 };
	const double d2{ 2011 };
	constexpr MyDouble myDouble1(d1);
	constexpr MyDouble myDouble2(2014);

	constexpr bool res = isLessThan(myDouble1, myDouble2);
	
	std::cout << "isLessThan(myDouble1, myDouble2): "
		<< res << '\n';

	std::cout << '\n';

}

namespace rewriting
{
	class MyInt {
	public:
		constexpr MyInt(int val)
		: value{ val }
		{ }
		auto operator<=>(const MyInt& rhs) const = default;
	private:
		int value;
	};

	void main() {

		std::cout << '\n';

		constexpr MyInt myInt2011(2011);
		constexpr MyInt myInt2014(2014);

		constexpr int int2011(2011);
		constexpr int int2014(2014);

		if (myInt2011 < myInt2014) std::cout << "myInt2011 < myInt2014" << '\n';
		if ((myInt2011 <=> myInt2014) < 0) std::cout << "myInt2011 < myInt2014" << '\n';

		std::cout << '\n';

		if (myInt2011 < int2014) std::cout << "myInt2011 < int2014" << '\n';
		if ((myInt2011 <=> int2014) < 0) std::cout << "myInt2011 < int2014" << '\n';

		std::cout << '\n';

		if (int2011 < myInt2014) std::cout << "int2011 < myInt2014" << '\n';
		if (0 < (myInt2014 <=> int2011)) std::cout << "int2011 < myInt2014" << '\n';


		if (0 < (int2011 <=> myInt2014)) std::cout << "";
		
		std::cout << '\n';

	}
}


const auto mm{ 50 };

consteval int sqr(int a)
{
	a *= mm;
	return a * a;
}


consteval int sqr2(int a)
{
	for (auto i = 0u; i < 2u; i++)
		a *= a;
	if(a>100)
	{
		a *= 20;
	}
	return a;
}

int res = sqr(5);

void useConstEval()
{
	// int a = 100;
	// (++a)++;
	constexpr  auto x = sqr(5);
	const int d = 10;
	const int e = 15;
	const int f = e;
	constexpr auto y = sqr(f);
	constexpr auto z = sqr2(d);
}



struct MyBool
{
	template<typename T>
	explicit(!std::is_same<T,bool>::value) MyBool(T t)
	{
		std::cout << typeid(t).name() << std::endl;
	}
};

template<double d>
constexpr auto getDouble()
{
	return d;
}


struct ClassType
{
	int x;
	constexpr ClassType(int x) : x{ x } {}
};


template<ClassType cl>
auto getClassType()
{
	return cl.x;
}


std::unique_ptr<ClassType> get()
{
	return std::make_unique<ClassType>(4);
}

void useCPP20Templates()
{
	constexpr auto x = getDouble<4.55>();

	auto c1 = getClassType < ClassType{ 50 } > ();

	std::unique_ptr<ClassType> p{ new ClassType{5} };

	std::shared_ptr<ClassType> s{ get() };

	std::shared_ptr<ClassType> ss{ std::make_unique<ClassType>(4) };

	std::shared_ptr<ClassType> sss( std::move(p) );

	std::cout << typeid(ClassType).name() << std::endl;

	std::type_index thisTypeIndex{ typeid(ClassType) };
	
}


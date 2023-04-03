


#include <algorithm>
#include <complex>
#include <vector>

#include <memory>
#include <iostream>

class SP
{
	inline static int count = 0;
	int number;
public:
	SP(int number_ = 0) : number(number_) { ++count; }

	~SP()
	{
		std::cout << number << " " << count << std::endl;
	}
};

#if 0
template<typename T>
class complex
{
	T real;
	T imaginary;
public:
	constexpr complex(const T& re = T{}, const T& im = T{}) : real(re), imaginary(im) {}

	constexpr T get_real() const { return real; }
};
#endif


void useSmartPointers()
{
	using namespace std;

	shared_ptr<SP[]> p{new SP[10]};

	constexpr complex conc{ 7.88 };
	constexpr complex s{ 5.91 };
	constexpr auto t = conc + s;

	auto x = std::sin(conc);

	//constexpr  vector<int> w(5);

	//constexpr  vector v{ 1,4,8,12,34,66 };


}


template<typename T, typename U>
T doAdd( const T& t, const U& u = U{})
{
	return t + u;
}


#include <utility>

template<typename CB>
class CountCalls
{
private:
	CB callback;
	long calls = 0;
public:
	CountCalls(CB cb) : callback(cb) {}
	template<typename...Args>
	decltype(auto) operator()(Args&&... args)
	{
		++calls;
		return callback(std::forward<Args>(args)...);
	}
	long count() const
	{
		return calls;
	}
};


void useCountCallsWrapper()
{
	doAdd(44, 88L);
	doAdd<int>(25, 55L);
	doAdd<int, long>(93, 67L);


	CountCalls sc{ [](auto x, auto y)		// type of sc is deduced as CountCalls<TYPE_OF_THE_LAMBDA>
	{
		return x > y;
	} };

	std::vector v{ 3,1,2,5,4 };
	std::sort(v.begin(), v.end(),  std::ref(sc));

	std::cout << "Sorted with " << sc.count() << " calls\n";

	for(auto x : v)
	{
		std::cout << x << " ";
	}
	std::cout << "\n";

}


namespace ArgumentDeduction
{
	template<typename T1, typename T2, typename T3=T2>
	class C
	{
	public:
		C(T1 x = {}, T2 y= {}, T3 z ={}) {}
	};


	void usingC()
	{
		C  c1(22, 4.5, "hi");	// OK deduced: T1 is int, T2 is double, T3 is const char*	// "hi" by value is decayed to pointer

		//C<std::string> c2("hi", "my");	// ERROR: Only T1 explicitly defined
		//C<> c3(22, 4.5, "hi");			// ERROR: neither T1 nor T2 explicitly defined
	}
}


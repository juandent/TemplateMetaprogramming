#include "stdafx.h"

using namespace std;

template <typename ...Args>
auto make_vector( const Args& ... elems)
{
	return std::vector{ elems... };
}

std::vector v{ 1,2,3 };

void use_make_vector()
{
	auto x1 = make_vector(v, v);
	auto x2 = make_vector(v);
}

#include <atomic>
#include <execution>

template<typename CB>
class CountCalls
{
private:
	CB callback;
	std::atomic<long> calls;

public:
	CountCalls(CB cb) : callback(cb) {}
	CountCalls(const CountCalls& cc) : callback(cc.callback)
	{
		calls.store(cc.calls.load());
	}
	
	template<typename ...Args>
	decltype(auto) operator()(Args&&...args)
	{
		++calls;
		return callback(std::forward<Args>(args)...);
	}
	long count() const
	{
		return calls;
	}
};



void useCountCalls()
{
	CountCalls sc{ [](auto x, auto y)
	{
		return x > y;
	} };

	vector v{ 3,5,8,2,1,0 };

	sort(v.begin(), v.end(), std::ref(sc));

	cout << "sorted with " << sc.count() << " calls" << endl;


	auto fo = for_each(v.begin(), v.end(), CountCalls{ [](auto i)
	{
		cout << "elem: " << i << endl;
	}
		});

	cout << "output with " << fo.count() << " calls\n";
	
	sort(std::execution::par, v.begin(), v.end(), std::ref(sc));
	
	std::tuple t{ 41,56.6 };	
}


template<typename T1, typename T2>
struct Pair1
{
	T1 first;
	T2 second;
	Pair1(const T1& x, const T2& y) : first{ x }, second{ y } {}
	// Pair1(T1 x, T2 y) : first{ x }, second{ y } {}
};

// deduction guides
template<typename T1, typename T2>
Pair1(T1, T2)->Pair1<T1, T2>;



void usePair1()
{
	const char x[3] = "hi";
	const char y[6] = "World";

	// char first[3]{ x };
	// char second[6]{ y };


	Pair1 p1{ "hi", "world" };

}

template<typename T>
struct S
{
	T val;
};

S(const char*)->S<string>;

void useS()
{
	S s1{ "hello" };
	S s2 = { "hello" };
	S s3 = S{ "hello" };

}


template<typename T>
struct S2
{
	T val;
};

explicit S2(const char*)->S2<string>;

void useS2()
{
	S2 s1{ "hello" };
//	S2 s2 = { "hello" };
	S2 s3 = S2{ "hello" };
}


template<typename T>
struct Ptr
{
	T t;
	
	Ptr(T a) : t{ a }
	{
		cout << t << " Ptr(T)\n" << typeid(T).name() << endl;;
	}

	template<typename U>
	Ptr(U a)
	{
		cout <<  a <<  " " << t << " Ptr(U)\n" << typeid(U).name() << endl;
	}
};

template<typename T>
explicit Ptr(T)->Ptr<T*>;


template<typename T>
void print( T&& t)
{
	cout << "ptr: " << typeid(t).name() << endl;
}



void usePtr()
{
	Ptr p1{ 42 };	// deduces Ptr<int*> due to guide
	print(p1);
	Ptr p2 = 42;	// deduces Ptr<int>  constructor
	int i = 42;	
	Ptr p3{ &i };	// deduces Ptr<int**> due to guide
	print(p3);
	Ptr p4 = &i;		// deduces Ptr<int*> constructor
	print(p4);
	Ptr p5 = Ptr{ 35 };	// deduces Ptr<int*> due to guide
	print(p5);
}


template<typename T>
struct A
{
	T val;
};

A(const char*)->A<string>;
// A(int)->A<int>;

template<typename T>
A(T)->A<T>;

void useAGuide()
{
	A i1{ 42 };
	A s3{ "hi" };
	
}


#include <map>

namespace std
{
	// template<typename Key, typename T, typename Compare = less<Key>, typename Allocator= allocator<pair<const Key, T>>>
	// map(initializer_list<pair<const Key, T>>, 
	// 	Compare = Compare(), 
	// 	Allocator = Allocator())
	// ->map<Key, T, Compare, Allocator>;

	// template<typename Key, typename T, typename Compare = less<Key>, typename Allocator = allocator<pair<const Key, T>>>
	// map(initializer_list<pair<Key, T>>,
	// 	Compare = Compare(),
	// 	Allocator = Allocator())
	// 	->map<Key, T, Compare, Allocator>;

	void useMap()
	{
		pair elem1{ 1,2 };
		pair elem2{ 3,4 };
		std::map m{ elem1, elem2 };
		
	}
}


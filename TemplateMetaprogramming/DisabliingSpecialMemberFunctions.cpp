
#include <iostream>
#include <type_traits>


namespace
{


	class C
	{
	public:
		template<typename T>
		C(T const&)
		{
			std::cout << "Template copy constructor\n";
		}
		C() = default;
		C(C const volatile&) = delete;
	};

	template<typename T>
	class Array {
	private:
		T* data;
	public:
		Array(T* data) : data(data) {}
		Array(Array<T> const&) = default;
		Array<T>& operator= (Array<T> const&) = default;
		void exchangeWith(Array<T>* b) {
			T* tmp = data;
			data = b->data;
			b->data = tmp;
		}
		T& operator[] (std::size_t k) {
			return data[k];
		}
	};

	template<typename T>
	void quickExchange(T*a, T*b)
	{
		T tmp(*a);
		*a = *b;
		*b = tmp;
	}

	template<typename T>
	void quickExchange( Array<T>* a, Array<T>* b)
	{
		a->exchangeWith(b);
	}

	struct S
	{
		int x;
	} s1, s2;

	void demo()
	{
		int list1[]{ 1,2,3 };
		int list2[]{ 6,7,8 };
		Array<int> a1{list1}, a2{list2};
		int* p = &a1[0];
		int* q = &s1.x;
		a1[0] = s1.x = 1;
		a2[0] = s2.x = 2;
		quickExchange(&a1, &a2);
		int pp = *p;
		quickExchange(&s1, &s2);
		int qq = *q;
	}



}


namespace X
{
	template<typename T>
	void f(T& x) {
		std::cout << "lvalue reference\n";
	}

	template<typename T>
	void f(T&& x) {
		std::cout << "rvalue reference\n";
	}

	class C {
	public:
		C() = default;
		C(C const&) {
			std::cout << "copy constructor\n";
		}
		C(C&&) {
			std::cout << "move constructor\n";
		}
		template<typename T>
		C(T&& x) {
			f(std::forward<T>(x));
			// decltype(auto) xx = std::forward<T>(x);
			std::cout << "template constructor\n";
		}
	};
	void main()
	{
		C x;
		C x2{ x };             // prints: template constructor
		C x3{ std::move(x) };  // prints: move constructor
		C const c;
		C x4{ c };             // prints: copy constructor
		C x5{ std::move(c) };  // prints: template constructor
	}
}



namespace CppTemplates
{
	void use()
	{
		C x;
		C y{ x };

		demo();
		X::main();
	}
}

#include <iostream>
#include <iterator>
#include <array>


namespace too_specific
{
	void need(int i)
	{
		std::cout << "int: " << i << std::endl;

	}

	void main()
	{
		std::cout << std::boolalpha << std::endl;
		double d{ 1.234 };
		std::cout << "double: " << d << std::endl;
		need(d);		// double -> int: narrowing conversion

		std::cout << std::endl;

		bool b{ true };
		std::cout << "bool: " << b << std::endl;
		need(b);		// bool -> int: integral promotion

	}
}




namespace overloads	// code repetition
{
	void need(int i)
	{
		std::cout << "int: " << i << std::endl;
	}
	void need(double d)
	{
		std::cout << "double: " << d << std::endl;
	}
	void need(bool b)
	{
		std::cout << "bool: " << b << std::endl;
	}

}

namespace generic_open
{
	template<typename T>
	void need(T t)
	{
		auto name = typeid(T).name();
		std::cout << name << ": " << t << std::endl;
	}
	class A {};

	void main()
	{
		need(5);
		need(4.578);
		A a{};
		//need(a);	// error C2679: binary '<<': no operator found which takes a right-hand operand of type 'T' (or there is no acceptable conversion)
	}

}


namespace generic_with_concept
{
	template<typename T>
	concept streamable = requires (T t, std::ostream os)
	{
		os << t;
	};


	template<typename T> requires streamable<T>
	void need(T t)
	{
		std::cout << "Value: " << t << std::endl;
	}

	template<streamable T>
	void need_2(T t)
	{
		std::cout << "Value: " << t << std::endl;
	}

	class A{};


	void main()
	{
		A a{};
		need(5);
		need(true);
		need(3.14);
		need_2(5);
		//need_2(a);	//  error C2672: 'need_2': no matching overloaded function found
	}
}

struct A
{
	int value;
};

int operator%(const A& a, const A& b)
{
	return a.value % b.value;
}


#include <cmath>

namespace modulus
{
	template<typename T> requires std::is_integral_v<T>
	T mod(T t1, T t2)
	{
		return t1 % t2;
	}
	template<typename T> requires std::is_floating_point_v<T>
	T mod(T t1, T t2)
	{
		return std::fmod(t1, t2);
	}

	void main()
	{
		auto r = mod(5, 3);

		auto s = mod(6.67, 33.10);
		auto t = mod(8.4f, 3.14159f);
		auto u = mod(7.77l, 5.54l);
	}
}


template<typename T>
class List
{
	struct Node
	{
		T data;
		std::shared_ptr<Node> next;
		inline static size_t count = 0;
		Node(T d, const std::shared_ptr<Node>& n) : data{d}
		{
			next = n;
			++count;
			std::cout << "ctor: " << count << std::endl;
		}
		Node(T d) : data(d), next(nullptr) {}
		~Node()
		{
			--count;
			std::cout << "dtor: " << count << std::endl;
		}
	};
	std::shared_ptr<Node> head;
	mutable std::shared_ptr<Node> curr;

public:
	void append(T const& t)
	{
		auto node = std::make_shared<Node>(t);

		if( head )
		{
			curr = head;
			while(curr->next)
			{
				curr = curr->next;
			}
			curr = node;
		}
		else
		{
			head = node;
		}
	}
	inline size_t length() const
	{
		size_t count = 0;
		if (head)
		{
			curr = head;
			while (curr->next)
			{
				curr = curr->next;
				++count;
			}
		}
		return count;
	}
};

template<>
class List<void*>
{
	struct Node
	{
		void* address;
		std::shared_ptr<Node> next;
	};
	std::shared_ptr<Node> head;
	mutable std::shared_ptr<Node> curr;

public:
	List() : head{ nullptr }, curr{ nullptr } {}

	void append(void* p)
	{
		auto node = std::make_shared<Node>(p, nullptr);

		if (head == nullptr)
		{
			head = node;
		}
		else
		{
			curr = head;
			while (curr->next)
			{
				curr = curr->next;
			}
			curr->next = node;
		}
	}
	inline std::size_t length() const
	{
		size_t count = 0;
		if (head)
		{
			curr = head;
			while (curr->next)
			{
				curr = curr->next;
				++count;
			}
		}
		return count;
	}
};



template<typename T>				// template partial specification
class List<T*>						// template arguments for this template definition have been only partially specified
{
	List<void*> impl;
public:
	inline void append(T* p)
	{
		impl.append(p);
	}
	inline size_t length() const
	{
		return impl.length();
	}
};

class Element
{
	std::string name;
	inline static size_t count = 0;
public:
	Element(std::string name) : name{ name } { ++count; }
	~Element() { --count; }
};


void useListTemplate()
{
	List<Element> list;
	list.append(Element{ "Juan" });
	list.append(Element{ "Roberto" });
	
}








template<std::random_access_iterator T>
void str()
{}

template<std::input_iterator T>
void str()
{}

using namespace std;

template<typename T>
concept is_iter_concept = requires { typename _Iter_concept<T>; };

template<typename T> requires is_iter_concept<T>
constexpr bool is_iter(T t)
{
	return true;
}

constexpr bool is = is_iter_concept<int[]>;

void useIter()
{
	std::array<int, 10> a;
	using type = typename _Iter_concept<decltype(begin(a))>;


	constexpr bool ok = is_iter(5);
}



template <class _It>
concept input_iterator = input_or_output_iterator<_It> && indirectly_readable<_It>
&& requires { typename _Iter_concept<_It>; }
&& derived_from<_Iter_concept<_It>, input_iterator_tag>;



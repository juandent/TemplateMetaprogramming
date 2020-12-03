#include "stdafx.h"

#include <unordered_set>


using namespace std;

template<typename T>
const T& spaceBefore(const T& arg)
{
	cout << ' ';
	return arg;
}

template<typename First, typename... Args>
void print(const First& f, const Args& ...args)
{
	cout << f;
	(cout << ... << spaceBefore(args)) << endl;;
}


template<typename First, typename... Args>
void printLambda(const First& f, const Args& ...args)
{
	cout << f;
	decltype(auto) spaceBefore = [](const auto& arg) -> const auto&
	{
		cout << ' ';
		return arg;
	};
	(cout << ... << spaceBefore(args)) << endl;;
}



template<typename First, typename... Args>
void printLambdaInline(const First& f, const Args& ...args)
{
	cout << f;
	(cout << ... << [](const auto& arg)// -> decltype(auto)
	{
			cout << ' ';
			return arg;
	}(args)) << endl;

}


template<typename First, typename... Args>
void printLambdaInlineConcise(const First& f, const Args& ...args)
{
	cout << f;
	auto outWithSpace = [](const auto& arg) -> decltype(auto)
	{
		cout << ' ' << arg;
	};

	(..., outWithSpace(args));		// (outWithSpace(arg1), outWithSpace(arg2)),outWithSpace(arg3)......
}


struct X
{
	int a {};
	X() = default;
	X( const X& x)
	{
		a = x.a;
	}

	friend ostream& operator <<( ostream&s, const X& x)
	{
		cout << x.a;
		return s;
	}
};


void usePrintSpaceBefore()
{
	X x{};
	
	printLambda(4, 6.8, "hello", x);
	printLambdaInline(4, 6.8, "hello", x);
	printLambdaInlineConcise(4, 6.8, "hello", x);
}


template<typename T>
void hashCombine( size_t& seed, const T& val)
{
	seed ^= hash<T>{}(val)+0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename ...Types>
size_t combinedHashValue( Types&&... args)
{
	size_t seed = 0;
	(..., hashCombine(seed, args));
	return seed;
}

struct Customer
{
	string first;
	string last;
	int value;

public:
	Customer( const string& f, const string& l, int v) : first(f), last(l), value(v)
	{}
	string getFirst() const { return first; }
	string getLast() const { return last; }
	int getValue() const { return value; }

	friend bool operator==( const Customer& l, const Customer& r)
	{
		return l.value == r.value && l.first == r.first && l.last == r.last;
	}

	friend ostream& operator<<(ostream& os, const Customer& c)
	{
		os << c.first << " " << c.last << " " << c.value;
		return os;
	}
};


struct CustomerHash
{
	size_t operator()(const Customer& c)
	{
		return combinedHashValue(c.getFirst(), c.getLast(), c.getValue());
	}
};

namespace std
{
	template<>
	struct hash<Customer>
	{
		size_t operator()(const Customer& c) const noexcept
		{
			return combinedHashValue(c.getFirst(), c.getLast(), c.getValue());
		}
	};
}


unordered_set<Customer, CustomerHash> a_set_of_customers;
unordered_set<Customer> another_set_of_customers;

unordered_map<string, Customer> a_map_of_customers;


void useHashCustomer()
{
	auto hasher = another_set_of_customers.hash_function();
	auto c = Customer{ "juan", "dent",200 };
	auto h = hasher(c);
	cout << h << endl;

	auto const j = string{ "juan" };
	
	pair juan{ j, c };
	a_map_of_customers.insert(juan);

	auto r = a_map_of_customers.find(j);
	if( r != a_map_of_customers.end())
	{
		cout << r->first << " " << r->second << endl;
	}
}


template<typename ...Bases>
class Multibase : private Bases...
{
public:
	void print()
	{
		(..., Bases::print());
	}
};

struct A
{
	void print() { cout << "A::print()" << endl; }
};

struct B
{
	void print() { cout << "B::print()" << endl; }
};

struct C
{
	void print() { cout << "C::print()" << endl; }
};



void useMultibase()
{
	Multibase<A, B, C> mb;
	mb.print();

}


struct Node
{
	int value;
	Node* subLeft{ nullptr };
	Node* subRight{ nullptr };
	Node(int i) : value{ i } {}
	int getValue() const noexcept
	{
		return value;
	}

	static constexpr auto left = &Node::subLeft;
	static constexpr auto right = &Node::subRight;

	template<typename T, typename ...TP>
	static Node* traverse(T t, TP...tp)
	{
		return (t ->* ... ->* tp);
	}
};

void useTraverse()
{
	Node* root = new Node{ 0 };
	root->subLeft = new Node{ 1 };
	root->subLeft->subRight = new Node{ 2 };

	// traverse binary tree
	Node* node = Node::traverse(root, Node::left, Node::right);
	cout << node->getValue() << endl;

	node = root->*Node::left->* Node::right;
	cout << node->getValue() << endl;
	node = root->subLeft->subRight;
	cout << node->getValue() << endl;
	
}

template<typename T1, typename ...TN>
struct IsHomogeneous
{
	static constexpr bool value = (is_same_v<T1, TN> && ...);
};

template<typename T1, typename ...TN>
constexpr bool isHomogeneous( T1 t1, TN...tn)
{
	return ( is_same_v<T1, TN> && ... );
}

void useHomogeneous()
{
	constexpr bool is = IsHomogeneous<int, decltype(42)>::value;
	constexpr bool isf = isHomogeneous(3, 42, 77);
}


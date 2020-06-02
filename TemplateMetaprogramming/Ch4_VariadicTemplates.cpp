
#include <iostream>


using namespace std;
using namespace std::string_literals;

template<typename T, typename...Types>
void print( T first, Types... args)
{
	cout << first << '\n';
	if constexpr (sizeof...(args) > 0)
	{
		print(args...);
	}
}

namespace _alpha
{
	struct Node
	{
		int value;
		Node* left;
		Node* right;
		Node(int v = 0) : value{ v }, left{ nullptr }, right{ nullptr } {}
	};

	template<typename T, typename ...TP>
	Node* traverse(T np, TP ...paths)
	{
		return (np ->* ...->*paths);
	}

}

struct Node
{
	int value;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
	Node(int v = 0) : value{ v }, left{ nullptr }, right{ nullptr } {}
};

template<typename T>
T* traverse(T* last)
{
	return last;
}

template<typename T, typename U, typename...Vs >
auto traverse(T* root, U ptr_mem, Vs... ptr_mems)
{
	return traverse((root->*ptr_mem).get(), ptr_mems...);
}

namespace Ch4
{
	void usePrint()
	{
		print(1.4, "Hello", "Goodbye"s);
	}

	auto left = &Node::left;
	auto right = &Node::right;

	void useTraverse()
	{
		std::unique_ptr<Node> root(new Node{ 0 });
		root->left.reset(new Node{ 1 } );
		
		root->left->right.reset(new Node{ 2 });
		root->left->right->right.reset( new Node{ 3 });

		Node* node = traverse(root.get(), left, right, right);

		cout << node->value << endl;
	}
}



#pragma once

template<typename T>
class ListNode
{
public:
	T value;
	ListNode<T>* next = nullptr;
	~ListNode() 
	{
		std::cout << value.value << next << std::endl;
		delete next;	// if nullptr, delete does nothing!!
	}
};


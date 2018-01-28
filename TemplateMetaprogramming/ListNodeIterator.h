#pragma once


#include "ListNode.h"
//#include "IteratorFacade.hpp"
#include "IteratorFacadeByAccess.hpp"
#include "iteratorfacadeaccess.h"

#include <iterator>

#if 0
namespace IteratorByFacade
{
	template<typename T>
	class ListNodeIterator
		: public IteratorFacade<ListNodeIterator<T>, T,
		std::forward_iterator_tag>
	{
		ListNode<T>* current = nullptr;
	public:
		T & dereference() const {
			return current->value;
		}
		void increment() {
			current = current->next;
		}
		bool equals(ListNodeIterator const& other) const {
			return current == other.current;
		}
		ListNodeIterator(ListNode<T>* current = nullptr) : current(current) { }
	};

}
#endif

//namespace IteratorByFacadeAccess
//{
	template<typename T>
	class ListNodeIterator 	: public IteratorFacadeUsingAccess<ListNodeIterator<T>, T,	std::forward_iterator_tag>
	{
		friend class IteratorFacadeAccess;

		ListNode<T>* current = nullptr;

		T & dereference() const {
			return current->value;
		}
		void increment() {
			current = current->next;
		}
		bool equals(ListNodeIterator const& other) const {
			return current == other.current;
		}
	public:
		ListNodeIterator(ListNode<T>* current = nullptr) : current(current) { }
	};

//}
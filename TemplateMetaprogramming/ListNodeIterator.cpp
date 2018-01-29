#include "stdafx.h"

#include "ListNodeIterator.h"

namespace IteratorByFacadeAccess
{
	struct A
	{
		int value;
	};
}

void useListsNodeIterator()
{
	using namespace IteratorByFacadeAccess;

	auto head = std::unique_ptr<ListNode<A>>{ new ListNode<A>{15, new ListNode<A>{ 16, new ListNode<A>{17, nullptr}}} };

	auto iter = ListNodeIterator<A>{head.get()};
	auto value = *iter;
	auto val = iter->value;
	auto next = ++iter;
	auto post = iter++;
	auto eq = post == next;

}
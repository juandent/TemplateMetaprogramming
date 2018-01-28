#pragma once

//namespace IteratorByFacadeAccess
//{
	class IteratorFacadeAccess
	{
		// only IteratorFacade can use these definitions
		template<typename Derived, typename Value, typename Category, typename Reference, typename Distance>
		friend class IteratorFacadeUsingAccess;

		// required of all iterators
		template<typename Reference, typename Iterator>
		static Reference dereference(Iterator const& i)
		{
			return i.dereference();
		}

		// required of all iterators
		template<typename Iterator>
		static void increment(Iterator & i)
		{
			return i.increment();
		}

		template<typename Iterator>
		static bool equals(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs.equals(rhs);
		}
	};

//}


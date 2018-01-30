#pragma once

namespace IteratorByFacadeAccess
{
	class IteratorFacadeAccess
	{
		// only IteratorFacade can use these definitions
		template<typename Derived, typename Value, typename Category, typename Reference, typename Distance>
		friend class IteratorFacade;

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
			i.increment();
		}

		template<typename Iterator>
		static bool equals(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs.equals(rhs);
		}

		// required by bidirectional iterators
		template<typename Iterator>
		static void decrement(Iterator & i)
		{
			i.decrement();
		}

		// required by random access iterators
		// advance
		template<typename Iterator, typename Difference>
		static void advance(Iterator& i, Difference n)
		{
			i.advance(n);
		}


		//measureDistance
		template<typename Distance, typename Iterator>
		static Distance measureDistance(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs.measureDistance(rhs);
		}

	};

}


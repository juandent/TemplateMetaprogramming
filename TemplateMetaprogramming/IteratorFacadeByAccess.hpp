#pragma once

#include "iteratorfacadeaccess.h"

namespace IteratorByFacadeAccess
{
	template<typename Derived, typename Value, typename Category,
		typename Reference = Value & , typename Distance = std::ptrdiff_t>
		class IteratorFacade
	{
		Derived& asDerived() { return *static_cast<Derived*>(this); };
		Derived const& asDerived() const { return *static_cast<Derived const*>(this); };

		static bool areEqual(const IteratorFacade& lhs, const IteratorFacade& rhs)
		{
			return IteratorFacadeAccess::equals(lhs.asDerived(), rhs.asDerived());
		}

		static Distance measureDistance(const IteratorFacade& lhs, const IteratorFacade& rhs)
		{
			return IteratorFacadeAccess::measureDistance<Distance>(lhs.asDerived(), rhs.asDerived());
		}
	public:
		using value_type = typename std::remove_const<Value>::type;
		using reference = Reference;
		using pointer = Value * ;
		using difference_type = Distance;
		using iterator_category = Category;

		// input iterator interface:
		reference operator *() const
		{
			return IteratorFacadeAccess::dereference<reference>(asDerived());
		}

		pointer operator ->() const
		{
			return &IteratorFacadeAccess::dereference<reference>(asDerived());
		}
		Derived& operator ++()
		{
			IteratorFacadeAccess::increment(asDerived());
			return asDerived();
		}
		// post-increment
		Derived operator ++(int)
		{
			Derived result(asDerived());
			IteratorFacadeAccess::increment(asDerived());
			return result;
		}
		friend bool operator== (IteratorFacade const& lhs, IteratorFacade const& rhs)
		{
			return IteratorFacade::areEqual(lhs, rhs);
		}
		friend bool operator!= (IteratorFacade const& lhs, IteratorFacade const& rhs)
		{
			return !(lhs==rhs);
		}


		// bidirectional iterator interface:
		Derived& operator--()
		{
			IteratorFacadeAccess::decrement(asDerived());
			return asDerived();
		}
		// post-decrement
		Derived operator--(int)
		{
			Derived result(asDerived());
			IteratorFacadeAccess::decrement(asDerived());
			return result;
		}

		// random access iterator interface:
		reference operator [](difference_type n) const 
		{ 
			Derived result{ asDerived() };
			IteratorFacadeAccess::advance(result, n);
			return *result;		// access dereference
		}
		Derived& operator +=(difference_type n) 
		{ 
			IteratorFacadeAccess::advance(asDerived(), n);
			return asDerived();
		}

		friend difference_type operator -(IteratorFacade const& lhs, IteratorFacade const& rhs) 
		{ 
			return IteratorFacade::measureDistance(lhs, rhs);
		}
		friend bool operator <(IteratorFacade const& lhs, IteratorFacade const& rhs) 
		{ 
			auto distance = IteratorFacade::measureDistance(lhs, rhs);
			return distance < 0;
		}
	};

}

#pragma once

#include "iteratorfacadeaccess.h"

//namespace IteratorByFacadeAccess
//{
	template<typename Derived, typename Value, typename Category,
		typename Reference = Value & , typename Distance = std::ptrdiff_t>
		class IteratorFacadeUsingAccess
	{
		Derived& asDerived() { return *static_cast<Derived*>(this); };
		Derived const& asDerived() const { return *static_cast<Derived const*>(this); };

		static bool areEqual(const IteratorFacadeUsingAccess& lhs, const IteratorFacadeUsingAccess& rhs)
		{
			return IteratorFacadeAccess::equals(lhs.asDerived(), rhs.asDerived());
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

		friend bool operator== (IteratorFacadeUsingAccess const& lhs, IteratorFacadeUsingAccess const& rhs)
		{
			return IteratorFacadeUsingAccess::areEqual(lhs, rhs);
		}
#if 0	
		// bidirectional iterator interface:
		Derived& operator --() { //... }
			Derived operator --(int) { //... }

									   // random access iterator interface:
				reference operator [](difference_type n) const { //... }
					Derived& operator +=(difference_type n) { //... }
															  //...
						friend difference_type operator -(IteratorFacade const& lhs, IteratorFacade const& rhs) { //... }
							friend bool operator <(IteratorFacade const& lhs, IteratorFacade const& rhs) { //... }
																										   //...
#endif
	};

//}
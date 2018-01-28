#pragma once

namespace IteratorByFacade
{

	template<typename Derived, typename Value, typename Category,
		typename Reference = Value & , typename Distance = std::ptrdiff_t>
		class IteratorFacade
	{
		Derived& asDerived() { return *static_cast<Derived*>(this); };
		Derived const& asDerived() const { return *static_cast<Derived const*>(this); };

	public:
		using value_type = typename std::remove_const<Value>::type;
		using reference = Reference;
		using pointer = Value * ;
		using difference_type = Distance;
		using iterator_category = Category;

		// input iterator interface:
		reference operator *() const
		{
			return asDerived().dereference();
		}

		pointer operator ->() const
		{
			return &asDerived().dereference();
		}
		Derived& operator ++()
		{
			asDerived().increment();
			return asDerived();
		}
		// post-increment
		Derived operator ++(int)
		{
			Derived result(asDerived());
			asDerived().increment();
			return result;
		}
		friend bool operator== (IteratorFacade const& lhs, IteratorFacade const& rhs)
		{
			return lhs.asDerived().equals(rhs.asDerived());
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

}
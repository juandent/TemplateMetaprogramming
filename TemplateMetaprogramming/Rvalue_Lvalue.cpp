#include "stdafx.h"

namespace JD
{
	using std::vector;
	using std::initializer_list;
	using std::shared_ptr;

	template<class S>
	S&& forward(typename std::remove_reference<S>::type& a) noexcept
	{
		return static_cast<S&&>(a);
	}

	template<typename T, typename Arg>
	std::shared_ptr<T> factory(Arg&& arg)
	{
		return shared_ptr<T>(new T(JD::forward<Arg>(arg)));

		//return shared_ptr<T>(new T(arg));
	}

#if 0
	template<class S>
	S&& forward( typename std::remove_reference<S>::type& a) noexcept
	{
		return static_cast<S&&>(a);
	}
#elif 0
	template<class S>
	S&& forward(S& a) noexcept
	{
		return static_cast<S&&>(a);
	}
#endif

	struct C
	{
		vector<int> values;

		C(const initializer_list<int>& list) 
		: values{list}{}

		C(const C& rhs) 
		: values{values} {}
		C(initializer_list<int>&& list)
		: values{std::move(list)}  {}

	};

	initializer_list<int> get_ints()
	{
		return { 2,4,6,8 };
	}

	initializer_list<int> list{ 1,2,3,4,5 };

	template<typename X>
	X&& forwarder(X& a) noexcept
	{
		return static_cast<X&&>(a);
	}


	void useFactory()
	{
		auto copied = factory<C>(list);
		auto ints = get_ints();
		auto moved_ints = factory<C>(ints);
		auto moved = factory<C>(get_ints());

		int i = 0;
		auto type = static_cast<int&>(i);
		decltype(auto) t = static_cast<int&>(i);
		decltype(auto) m = forwarder(i);
		auto val = 3.14;


		::std::forward<C>(list);

	}

}
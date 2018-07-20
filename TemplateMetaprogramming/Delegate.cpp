#include "stdafx.h"
#include "Delegate.h"









#if 0
template<typename R, typename Class, typename ...Args>
Invoker<R, Class, ...Args>::Invoker(R(Class::*p)(Args...))
{
}
#endif

#if 0
template<typename R, typename Class>
R invoker(R(Class::*p))
{
	return R{};
}
#endif

using Pmemfun = int (Something::*)(int, int);

template<typename ...Args>
int invoker(Something* pp, Pmemfun m, Args... args)
{
	return (pp->*m)(args...);
}

template<typename R, typename Class, typename...Args>
auto general_invoker(Class* pp, R(Class::*m), Args...args)
{
	return (pp->*m)(args...);
}

template<typename R, typename Class, typename...Args>
auto general_inv(Class* pp, R(Class::*m), Args...args)
{
	return (pp->*m)(args...);
}


template<typename MemberFunction, typename Class>
struct Delegate
{
	Class* m_target;
	std::vector<MemberFunction> m_functions;

	Delegate( Class* target, std::initializer_list<MemberFunction> functions)
		: m_target(target), m_functions{functions}
	{
	}

	template <typename ...Args>
	auto	Invoke( Args... args)
	{
		for (auto& f : m_functions)
		{
			auto res = (m_target->*f)(args...);
		}
	}
};

///// each delegate type is associated with one specific signature!!!
///// and 1 or more methods to be called

void useInvoker()
{
	Something s{ 4 };

	int(Something::*point)(int, int) = &Something::max;

	int r = invoker(&s, &Something::max, 4, 7);

	Delegate<Pmemfun, Something> delegate(&s, {&Something::max });
		
	delegate.Invoke(4, 8);
		
}

#include "stdafx.h"


void makeLogEntry(std::string s) {}

struct Widget
{
	std::vector<int> m_vector;
	Widget(int number) : m_vector({ number }) {}
	Widget(const Widget& w) : m_vector{ w.m_vector} { std::cout << "copy ctor\n"; }
	// Widget(Widget&& w) : m_vector{ w.m_vector } { w.m_vector.clear();  std::cout << "move ctor\n"; }

	Widget(Widget&& w) = default;
};



void process( const Widget& lvalArg)
{
	std::cout << "Handling lvalue\n";
}

void process(Widget&& rvalArg)
{
	std::cout << "Handling rvalue\n";
}


template<typename T>
void LogAndProcessWithUR(T&& param)
{
	makeLogEntry("calling processs");
	process(std::forward<T>(param));
}

template<typename T>
void LogAndProcess(T param)		// no universal reference
{
	if (std::is_rvalue_reference_v<T>)
	{
		std::cout << "T is rvalue reference\n";
	}
	if (std::is_rvalue_reference_v<decltype(param)>)
	{
		std::cout << "param is rvalue reference\n";
	}

	makeLogEntry("calling processs");
	process(std::forward<T>(param));	// ALWAYS forwards to process(Widget&&) regardless of the object passed
}


void testForwarding()
{
	process(Widget{ 4 });	// call with rvalue
	Widget w{ 5 }, q{ 7 };
	process(w);

	LogAndProcess(Widget{ 4 });
	LogAndProcess(std::move(w));

	LogAndProcessWithUR(Widget{ 4 });
	LogAndProcessWithUR(std::move(q));

}

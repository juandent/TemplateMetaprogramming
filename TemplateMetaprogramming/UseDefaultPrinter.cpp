

// #include <ranges>
// #include <concepts>

#include <iostream>
#include <ostream>

import DefaultPrinter;

void usep()
{
	DefaultPrinter printer{};

	printer.print_eol();
	std::cout << "a" << std::endl;
}


template<typename T>
struct Series
{
    T val{ 0 };
	
    T next() { return ++val; }
    bool done() { return val == 8; }
};

// template<typename T>
// concept is_series = std::is_same_v<T, Series<int>>;


template<typename T>
concept is_series = requires (T t, int a)
{
    t.val;
    a = t.next();
    t.done() && true ;
};




struct DefaultFormatter
{
    template<is_series S, typename T> ///requires std::is_same_v<S, Series<int>>
    void format(T t, S s)
    {
        while (!s.done())
        {
            t.print_element(s.next());
            t.print_separator();
        }
        t.print_eol();
    }
};

void usedef()
{
    constexpr bool is = is_series<Series<int>>;

    Series<int> ser;
    DefaultPrinter p;
    DefaultFormatter df;

	df.format(p, ser);
}

#include <type_traits>
#include <iostream>


template<typename T> constexpr bool always_false = false;

template<typename T>
typename std::add_rvalue_reference<T>::type declval() noexcept {
    static_assert(always_false<T>, "declval not allowed in an evaluated context");
}




/**
  *  Constraints a deleter to be or to yield a function pointer.
  */
template<typename D>
concept yields_fp = requires(D d) {
    // yielding function pointer by using the plus trick
    {+d};
        requires std::is_function_v<std::remove_pointer_t<decltype(+d)>>;
        //requires std::is_function_v<std::remove_pointer_t<decltype(+std::declval<D>())>>;
};


template<typename D>
concept yields = requires {
    requires std::is_function_v<std::remove_pointer_t<decltype(+std::declval<D>())>>;
};



void ff(void) {}

auto demo(yields_fp auto arg) {
    arg();
}

struct XC
{
    void operator()()
    {
        std::cout << "Hello\n";
    }
};

auto lam = []()
{
};

void useConceptYields_fp() {
    demo(ff);
    using type = decltype((lam));
    type t = lam;
    using type2 = decltype(lam);
    type2 tt;
    using type3 = decltype(+lam);
    type3 ttt;
    demo(lam);
}


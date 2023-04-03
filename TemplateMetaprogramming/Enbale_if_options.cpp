
#include <iostream>
#include <type_traits>


#define USING_CONCEPTS
#ifdef USING_CONCEPTS
template<class T>
    requires (!std::is_array_v<T> && !std::is_pointer_v<T>)
void destroy(T t)
{
    // detroy t
}

template<class T>
requires ( std::is_array_v<T>)
void destroy(T* t)
{
    for (std::size_t i = 0; i < std::extent<T>::value; ++i) {
        destroy((*t)[i]);
    }
}


#else
template<class T>
std::enable_if<! std::is_array_v<T>  &&  ! std::is_pointer_v<T>>::type
destroy(T t)
{
	// destroy t
}
#endif

//#define VIA_RETURN_TYPE
#ifdef VIA_RETURN_TYPE
template<typename T>
std::enable_if<std::is_array<T>::value, void>::type
destroy(T* t)
{
    for (std::size_t i = 0; i < std::extent<T>::value; ++i) {
        destroy((*t)[i]);
    }
}
#endif

#ifdef VIA_PARAMETER
template<class T>
void destroy( T* t, typename std::enable_if< std::is_array<T>::value>::type* = 0)
{
    for (std::size_t i = 0; i < std::extent<T>::value; ++i) {
        destroy((*t)[i]);
    }
}
#endif


//#define VIA_NON_TYPE_TEMPLATE_PARAMETER
#ifdef VIA_NON_TYPE_TEMPLATE_PARAMETER
template<typename T, typename std::enable_if<std::is_array<T>::value, bool>::type = true >
void destroy(T* t)
{
    for (std::size_t i = 0; i < std::extent<T>::value; ++i) {
        destroy((*t)[i]);
    }
}
#endif


#ifdef VIA_TYPE_TEMPLATE_PARAMETER
// #5, enabled via a type template parameter
template<typename T, typename = std::enable_if<std::is_array<T>::value>::type >
void destroy(T* t) 
{
    for (std::size_t i = 0; i < std::extent<T>::value; ++i) {
        destroy((*t)[i]);
    }
}
#endif


#define UNRESTRICTED_GENERIC
#ifdef UNRESTRICTED_GENERIC
template<class T>
void destroy(T* t)
{
    for (std::size_t i = 0; i < std::extent<T>::value; ++i) {
        destroy((*t)[i]);
    }
}
#endif


#ifdef USING_CONCEPTS
template<typename T>
    requires (std::is_floating_point_v<T>)
T moduloOf(T a, T b)
{
    return std::fmod(a, b);
}
template<typename T>
    requires (std::is_integral_v<T>)
T moduloOf(T a, T b)
{
    return a % b;
}

#else
template<typename T, typename std::enable_if<std::is_integral<T>::value, T>::type = 0>
T moduloOf(T a, T b) {
    return a % b;
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, T>::type = 0>
T moduloOf(T a, T b) {
    return std::fmod(a, b);
}

#endif




namespace 
{
    struct A
    {
        ~A() = default;
        long x;
        A(long _x) : x{_x} {}
    };
}


namespace JD
{
    template <class _Ty, _Ty _Val>
    struct integral_constant {
        static constexpr _Ty value = _Val;

        using value_type = _Ty;
        using type = integral_constant;

        constexpr operator value_type() const noexcept {
            return value;
        }

        _NODISCARD constexpr value_type operator()() const noexcept {
            return value;
        }
    };
}

#pragma check_stack +

void useEnableIf()
{
    int arr1[] = { 1,2,3 };
    destroy(&arr1);
    auto int_ret = moduloOf(5, 8);
    auto float_ret = moduloOf(14.4L, 12.3L);

#ifdef UNRESTRICTED_GENERIC
    int* p = arr1;
    //destroy(p);
#endif

    char buff[4];
    char* b = buff;
//    b[-1] = 'a';
}

namespace Combination
{

    template <typename T>
    concept Integral = std::is_integral<T>::value;
    template <typename T>
    concept SignedIntegral = Integral<T> && std::is_signed<T>::value;
    template <typename T>
    concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;

    void func(SignedIntegral auto integ) {
        std::cout << "SignedIntegral: " << integ << '\n';
    }
    void func(UnsignedIntegral auto integ) {
        std::cout << "UnsignedIntegral: " << integ << '\n';
    }
    void main() {
        std::cout << '\n';
        func(-5);
        func(5u);
        std::cout << '\n';
    }

}

namespace FunctionTemplates
{
    template<typename T>
    concept Integral = std::is_integral<T>::value;

    template<typename T>
        requires Integral<T>
    T gcd(T a, T b) {
        if (b == 0) { return a; }
        else {
            return gcd(b, a % b);
        }
    }
    template<Integral T>
    T gcd1(T a, T b) {
        if (b == 0) { return a; }
        else {
            return gcd(b, a % b);
        }
    }
    Integral auto gcd2(Integral auto a, Integral auto b)
	{
        if (b == 0) { return a; }
        else {
            return gcd(b, a % b);
        }
    }

}

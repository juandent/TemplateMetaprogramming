//
//  Exercise 2_3_JLBorges.cpp
//  TemplateMetaprogramming
//
//  Created by Juan Dent on 11/January/17.
//  Copyright © 2017 Juan Dent. All rights reserved.
//

#include "stdafx.h"

#include "Exercise 2_3_JLBorges.hpp"

#include <iostream>
#include <string>
#include <array>

template <typename> struct extents { static std::string str() { return {}; } };

template < typename T > struct extents<T[]>
{ static std::string str() { return "[]" + extents<T>::str() ; } };

template < typename T, std::size_t N > struct extents< T[N] >
{ static std::string str() { return '[' + std::to_string(N) + ']' + extents<T>::str() ; } };

// JD next 2:
template < typename T, std::size_t N > struct extents< T(&)[N] >
{ static std::string str() { return "(&)[" + std::to_string(N) + ']' + extents<T>::str() ; } };

template < typename T, std::size_t N > struct extents< T(*)[N] >
{ static std::string str() { return "(*)[" + std::to_string(N) + ']' + extents<T>::str() ; } };

// end jd

template <typename> struct name { static std::string str() { return "'unknown type'" ; } };
template <> struct name<char> { static std::string str() { return "char" ; } };
template <> struct name<short> { static std::string str() { return "short" ; } };
template <> struct name<int> { static std::string str() { return "int" ; } };
template <> struct name<long> { static std::string str() { return "long" ; } };

// jd next:
template <> struct name<void> { static std::string str() { return "void" ; } };
// end jd

template < typename T > struct name< const T >
{ static std::string str() { return "const " + name<T>::str() ; } };

template < typename T > struct name< volatile T >
{ static std::string str() { return "volatile " + name<T>::str() ; } };

template < typename T > struct name< volatile const T >
{ static std::string str() { return "volatile const " + name<T>::str() ; } };

// TO DO: take care of pointers, references
// JDH ADDED:
template < typename T > struct name< T* >
{ static std::string str() { return name<T>::str() + "*" ; } };

template < typename T > struct name< T& >
{ static std::string str() { return name<T>::str() + "&" ; } };

template < typename T > struct name< T&& >
{ static std::string str() { return name<T>::str() + "&&" ; } };

template < typename T > struct name< T* const>
{ static std::string str() { return name<T>::str() + "* const" ; } };

template < typename T > struct name< T* volatile>
{ static std::string str() { return name<T>::str() + "* volatile" ; } };

template < typename T > struct name< T* const volatile>
{ static std::string str() { return name<T>::str() + "* const volatile" ; } };

template< typename ...Args> struct separator
{
    static const std::array<std::string, 2> constants;
};

template< typename ...Args>
const std::array<std::string, 2> separator<Args...>::constants = {"", ","};


template< typename ...Args> struct arg_names
{
    static std::string str() { return "Args..."; }
};

template<> struct arg_names<>
{
    static std::string str() { return ""; }
};

template < typename Arg0, typename ...Args> struct arg_names< Arg0, Args...>
{
    static std::string str() { return name<Arg0>::str() + separator<Args...>::constants[ sizeof...(Args) > 0] + arg_names<Args...>::str() ; } 
};

template < typename T > struct name< T(&)() >
{ static std::string str() { return name<T>::str() + "(&)()" ; } };

template < typename T, typename ...Args> struct name< T(&)(Args...) >
{ static std::string str() { return name<T>::str() + "(&)(" + arg_names<Args...>::str() + ")" ; } };


// END JDH ADDITIONS

template < typename T > struct base_type
{
    using type = T ;
    static std::string str() { return name<type>::str() ; }
};

template < typename T > struct base_type<T[]>
{
    using type = typename base_type<T>::type ;
    static std::string str() { return name<type>::str() ; }
};

template < typename T, std::size_t N > struct base_type< T[N] >
{
    using type = typename base_type<T>::type ;
    static std::string str() { return name<type>::str() ; }
};
// JD next 2 funcs:
template < typename T, std::size_t N > struct base_type< T(&)[N] >
{
    using type = typename base_type<T>::type ;
    static std::string str() { return name<type>::str() ; }
};

template < typename T, std::size_t N > struct base_type< T(*)[N] >
{
    using type = typename base_type<T>::type ;
    static std::string str() { return name<type>::str() ; }
};


// end jd

template < typename T > struct type_desc
{ static std::string str() { return base_type<T>::str() + ' ' + extents<T>::str() ; } };


// jd add next:
void funny()
{
    std::cout << "fun\n";
}
void funny(int i)
{
    std::cout << "funny\n";
}

void funny(int i, long l)
{
    std::cout << "funny\n";
}

void funny(int i, long l, char c)
{
    std::cout << "funny\n";
}

// end jd


void solve_2_3()
{
    using namespace std;
    const char cstr[] = "abcdefgh" ;
    int i = 0;
    int* p = &i;
    const int& r = i;
    int *a[3];
    
    const char* const * const pp = nullptr;
    cout << type_desc<decltype(pp)>::str() << endl;

    const char* const volatile * const ppp = nullptr;
    cout << type_desc<decltype(ppp)>::str() << endl;

    int v[14];
    int (&vr)[14] = v;
    cout << type_desc<decltype(vr)>::str() << endl;
    int ia[3][4];
    int (&vrr)[3][4] = ia;
    cout << type_desc<decltype(vrr)>::str() << endl;
    int (*par)[4] = ia;
    cout << type_desc<decltype(par)>::str() << endl;

    
    void (&pf)() = funny;
    cout << type_desc<decltype(pf)>::str() << endl;
    
    void (&pfi)(int) = funny;
    cout << type_desc<decltype(pfi)>::str() << endl;
    
    void (&pfil)(int,long) = funny;
    cout << type_desc<decltype(pfil)>::str() << endl;
    
    void (&pfilc)(int,long,char) = funny;
    cout << type_desc<decltype(pfilc)>::str() << endl;
    
    
    cout  << type_desc<decltype(p)>::str() << '\n'
    << type_desc< int *[3][4]>::str() << '\n'
    << type_desc< decltype(r)>::str() << '\n'
    << type_desc< decltype(a)>::str() << '\n';
    std::cout << type_desc<char>::str() << '\n' // char
    << type_desc< decltype(cstr) >::str() << '\n' // const char [9]
    << type_desc< short[] >::str() << '\n' // short []
    << type_desc< const short[7][5] >::str() << '\n' // const short [7][5]
    << type_desc< volatile int[5][3][8][6] >::str() << '\n' // volatile int [5][3][8][6]
    << type_desc< volatile const long[][3][8][6] >::str() << '\n' // volatile const long [][3][8][6]
    << type_desc< const std::string[6] >::str() << '\n' ; // const 'unknown type' [6] 
}


//
//  main.cpp
//  TemplateMetaprogramming
//
//  Created by Juan Dent on 19/August/16.
//  Copyright © 2016 Juan Dent. All rights reserved.
//

#include <iostream>
#include <boost/type_traits.hpp>


constexpr size_t rankkk = boost::rank<int[8][2]>::value;


template<typename Aggregate, typename Element>
struct Dimension
{
    static constexpr size_t value = boost::is_array<Aggregate>::value ? sizeof(Aggregate)/ sizeof(Element) : 0;
};

template<typename Element>
struct Dimension<void, Element>
{
    static constexpr size_t value = 0;
};

template<typename Base, size_t dim_number>
struct dim_count
{
    typedef typename dim_count<Base,dim_number-1>::element_type base_type;
    typedef typename boost::remove_bounds<base_type>::type element_type;
    static constexpr size_t value = Dimension<base_type, element_type>::value;
};

template<typename Base>
struct dim_count<Base, 0>
{
    typedef typename boost::remove_bounds<Base>::type element_type;
    static constexpr size_t value = Dimension<Base, element_type>::value;
};

template<typename T, size_t Num>
struct add_dim
{
    typedef T array[Num];
};

template<typename T>
struct strip_all
{
    typedef typename boost::remove_pointer<T>::type no_pointer;
    typedef typename boost::remove_reference<no_pointer>::type no_ptr_ref;
    typedef typename boost::remove_all_extents<no_ptr_ref>::type no_ptr_ref_ext;
    typedef typename boost::remove_cv<no_ptr_ref_ext>::type type;
};

template<typename T>
struct strip_each
{
    typedef typename boost::remove_pointer<T>::type no_pointer;
    typedef typename boost::remove_reference<T>::type no_ref;
    typedef typename boost::remove_all_extents<T>::type no_extents;
    typedef typename boost::remove_cv<T>::type no_cv;
};


// Compound several type functions into one
// Say: boost::remove_pointer<T>::type + boost::remove_const<T>::type
template<typename C, template <typename> class ...Removers>
struct CombineTypeFuncs
{
};

// General
template<typename C, template <typename> class First, template <typename> class ...Rest>
struct CombineTypeFuncs<C, First, Rest...>
{
    typedef typename First< typename CombineTypeFuncs<C, Rest...>::type>::type type;
};

// Finish
template<typename C, template <typename> class First>
struct CombineTypeFuncs<C, First>
{
    typedef typename First<C>::type type;
};


namespace JD
{
    template<typename T>
    struct remove_const_pointer
    {
    private:
        typedef typename boost::remove_pointer<T>::type firstType;
    public:
        typedef typename boost::remove_const<firstType>::type type;
    };
    
    template< typename T, template <typename> class Func1, template <typename> class Func2>
    struct CombineTypeFuncs
    {
        typedef typename Func2<typename Func1<T>::type>::type type;
    };
 }

// TODO: ApplyTypeFunction

struct Nil {};

template<template <typename> class RemoveFunction, template <typename> class AddFunction, typename C, typename X, typename Y>
struct Apply
{
    typedef typename boost::conditional<(boost::is_same<typename RemoveFunction<C>::type, X>::value), typename AddFunction<Y>::type, Nil>::type type;
};


template<typename c, typename x, typename y>
struct replace_type
{
//private:
    static constexpr bool c_is_const = boost::is_const<c>::value;
    static constexpr bool c_is_pointer = boost::is_pointer<c>::value;
    static constexpr bool c_is_array = boost::is_array<c>::value;
    static constexpr size_t c_rank = boost::rank<c>::value;
    static constexpr size_t c_dim_0 = dim_count<c, 0>::value;
    static constexpr size_t c_dim_1 = dim_count<c, 1>::value;
    typedef typename boost::remove_bounds<c>::type c_type_0;
    typedef typename boost::remove_bounds<c_type_0>::type c_type_1;

    static constexpr bool x_is_const = boost::is_const<x>::value;
    static constexpr bool x_is_pointer = boost::is_pointer<x>::value;
    static constexpr bool x_is_array = boost::is_array<x>::value;
    static constexpr size_t x_rank = boost::rank<x>::value;
    static constexpr size_t x_dim_0 = dim_count<x, 0>::value;
    static constexpr size_t x_dim_1 = dim_count<x, 1>::value;
    typedef typename boost::remove_bounds<x>::type x_type_0;
    typedef typename boost::remove_bounds<x_type_0>::type x_type_1;

    
    typedef typename strip_all<c>::type c_stripped;
    typedef typename strip_all<x>::type x_stripped;
    typedef typename strip_all<y>::type y_stripped;
    
    static constexpr bool stripped_are_same = boost::is_same<c_stripped, x_stripped>::value;
    
    
    struct x_is_in_c
    {
        // decomposing c into all its possible subvalues
        // FIRST, c in its entirety!!
        typedef c complete_c;
        static constexpr bool is_identical = boost::is_same<x, complete_c>::value;
        // how do they differ -- how can they differ?
        
        // c has one more pointer than x
        typedef typename boost::remove_pointer<complete_c>::type c_minus_1_ptr;
        static constexpr bool is_minus_1_ptr = boost::is_same<x, c_minus_1_ptr>::value;

        // c has one more const than x
        typedef typename boost::remove_const<complete_c>::type c_minus_const;
        static constexpr bool is_minus_const = boost::is_same<x, c_minus_const>::value;
        
        // c has one more pointer than x and one more const than x
        typedef typename boost::remove_const<c_minus_1_ptr>::type c_minus_1_ptr_minus_const;
        static constexpr bool is_minus_1_ptr_minus_const = boost::is_same<x, c_minus_1_ptr_minus_const>::value;
        
        
    };
    
    struct restore
    {
        static constexpr bool y_should_const = c_is_const && ! x_is_const;
        
        
        // if c_is_pointer, then restore pointer
        typedef typename boost::conditional<c_is_pointer, typename boost::add_pointer<y_stripped>::type, y_stripped>::type restored_pointer;
        // 
    };   
public:
    typedef typename boost::remove_pointer<c>::type c_minus_pointer;
    typedef typename boost::remove_const<c>::type c_minus_const;
    typedef typename boost::remove_const<c_minus_pointer>::type c_minus_const_minus_pointer;
    
    typedef typename boost::add_pointer<y>::type y_plus_pointer;
    typedef typename boost::add_const<y>::type y_plus_const;
    typedef typename boost::add_pointer<y_plus_const>::type y_plus_const_plus_pointer;
    
    static constexpr bool match_orig = boost::is_same<c, x>::value;
    static constexpr bool match_minus_pointer = boost::is_same<c_minus_pointer, x>::value;
    static constexpr bool match_minus_const = boost::is_same<c_minus_const, x>::value;
    static constexpr bool match_minus_const_minus_pointer = boost::is_same<c_minus_const_minus_pointer, x>::value;
    
    
    typedef typename boost::conditional< match_orig, y, c>::type match_orig_type;
    /*
    typedef typename boost::conditional< match_minus_pointer, y_plus_pointer, c>::type match_orig_type;
    
        typename boost::conditional< match_minus_pointer, y_plus_pointer,
            typename boost::conditional< match_minus_const, y_plus_const,
            typename boost::conditional< match_minus_const_minus_pointer, y_plus_const_plus_pointer, x>::type>>, x>::type>
    
    */
    
    
    typedef typename boost::conditional<stripped_are_same, typename restore::restored_pointer,c>::type type; 
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //constexpr auto x = sizeof(int);
    
    std::cout << std::boolalpha;
    
    using C = bool const *;
    
    typedef typename boost::remove_const<C>::type C_minus_const;
    typedef typename boost::remove_pointer<C_minus_const>::type C_minus_ptr_minus_const;
    
    std::cout << boost::is_same<C_minus_ptr_minus_const, bool>::value << std::endl;
    
    typedef typename CombineTypeFuncs<bool const*, boost::remove_const, boost::remove_pointer>::type Plain;
    
    Plain p {};
    
    std::cout << p <<  " Plain is bool: " << boost::is_same<Plain, bool>::value << std::endl;
    
    bool is_fund = boost::is_fundamental<void const>::value; 
    
    bool same = replace_type<void*, void, int>::stripped_are_same;
    
    typedef typename replace_type<void*, void, int>::type t;
    
    t aT  = nullptr;
    
    std::cout << boost::is_same<t, int*>::value  << " "  << typeid(t).name() <<  std::endl;
    
    
    constexpr auto v_1 = dim_count<int,0>::value;
    
    constexpr auto val0 = dim_count<int[8][2], 0>::value;
    
    std::cout << val0 << "\n";
    
    add_dim<int, val0>::array ar;
    
    add_dim<int[2], 4>::array another;
    
    
    auto val1 = dim_count<int[8][2], 1>::value;
    
    std::cout << val1 << "\n";

    auto val2 = dim_count<int[8][2], 2>::value;
    
    std::cout << val2 << "\n";

    return 0;
}

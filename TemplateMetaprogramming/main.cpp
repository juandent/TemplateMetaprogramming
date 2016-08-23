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


template<typename Aggregate, typename Element = typename boost::remove_bounds<Aggregate>::type>
struct Dimension
{
    static constexpr size_t value = boost::is_array<Aggregate>::value ? sizeof(Aggregate)/ sizeof(Element) : 0;
    typedef Element element_type;
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
    static constexpr size_t value = Dimension<base_type>::value;
    
};

template<typename Base>
struct dim_count<Base, 0>
{
    typedef typename boost::remove_bounds<Base>::type element_type;
    static constexpr size_t value = Dimension<Base>::value;
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

template<template<typename> class ...Elements>
struct TypeList
{
    
};

typedef TypeList<boost::remove_const, boost::remove_pointer> BasicTypes;


//template< TypeList
struct ListHolder
{
    
};


namespace experimental {


}


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

struct Nil {};

namespace JD
{
    template<typename C, typename X, typename Y>
    struct ApplyTypeFuncs
    {
        template<template<typename> class ...Removers>
        struct Remove
        {
            typedef typename CombineTypeFuncs<C, Removers...>::type c_type;
        };

        template<template<typename> class ...Adders>
        struct Add
        {
            typedef typename CombineTypeFuncs<Y, Adders...>::type y_type;
        };


        template<typename C_converted, typename Y_converted>
        struct Result
        {
            typedef typename boost::conditional<std::is_same<C_converted, X>::value, Y_converted, Nil>::type type;
        };
        
        //using Original = C;
        //using SearchType = X;
    };
    
    using namespace std;
    
    
    template<typename A, typename B>
    struct is_identical
    {
        //static constexpr bool value = std::is_
    };
    
    
    //template<typename C, typename X, typename Y>
    void doReplace_type()
    {
        /*
        typedef ApplyTypeFuncs<bool const*, bool, int> BaseType;
        
        typedef typename BaseType::Remove<boost::remove_const, boost::remove_pointer>::c_type C_Type;
        typedef typename BaseType::Add<boost::add_pointer, boost::add_const>::y_type Y_Type;
        typedef typename BaseType::Result<C_Type, Y_Type>::type ReturnType;
        
        std::cout << typeid(ReturnType).name() << std::endl;
*/
        using C = bool const;
        using X = bool;
        using Y = int;
        
        typedef ApplyTypeFuncs<C, X, Y> BaseType2;
        
        typedef typename std::remove_pointer<C>::type c_pointer;
        typedef typename std::remove_const<c_pointer>::type c_pointer_const;
        
        cout << std::is_same<C, c_pointer>::value << endl;
        cout << std::is_same<C, c_pointer_const>::value << endl;
    
        
        c_pointer c = true;
        c_pointer_const cc =  false;
        
        cout << typeid(C).name() << endl;
        cout << typeid(c_pointer).name() << endl;
        cout << typeid(c_pointer_const).name() << endl;
        
        typedef typename BaseType2::Remove<std::remove_const, std::remove_pointer>::c_type C_Type;
        typedef typename BaseType2::Add<std::add_pointer, std::add_const>::y_type Y_Type;
        
        cout << std::is_same<C_Type, X>::value << endl;
        
        typedef typename BaseType2::Result<C_Type, Y_Type>::type ReturnType;
        
        std::cout << typeid(ReturnType).name() << std::endl;

        
    }
    
}




namespace  TypeFuncList {    
    
    template< template <typename > class ...TypeFuncs >
    struct TypeFuncList
    {
        using type = TypeFuncList<TypeFuncs...>;
    };
    
    void useTypeFuncList()
    {
        typedef typename TypeFuncList<boost::remove_const, boost::remove_pointer, boost::remove_bounds>::type Removers;
        typedef typename TypeFuncList<boost::add_pointer, boost::remove_pointer, boost::remove_bounds>::type Adders;
    }
    
    template<typename ...Ts>
    struct Type 
    {
        using type = Type<Ts...>;
    };
    
    void useType()
    {
        typedef typename Type<int, bool, char>::type Integrals;
        Integrals integrals;
        
        
    }
}

// TODO: ApplyTypeFunction



// Search types type0, type1, ..., top find the first Not Nil!
template<typename ...types>
struct FirstNotNil
{
};

template<typename first, typename ...rest>
struct FirstNotNil<first, rest...>
{
    typedef typename boost::conditional<! boost::is_same<first, Nil>::value, first, typename FirstNotNil<rest...>::type>::type type; 
};

template<typename first>
struct FirstNotNil<first>
{
    // if first is not nil, return first --- else return nil
    typedef typename boost::conditional<boost::is_same<first, Nil>::value, Nil, first>::type type;
};



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
    
    
    //typedef typename boost::conditional<stripped_are_same, typename restore::restored_pointer,c>::type type;
    
    ////////////////////////////////////////// --- NEW PART ---------------
    
    // decomposing C:
    
    // is C identical to X?
    typedef typename boost::conditional< boost::is_same<c,x>::value, y, Nil>::type type0;
    
    // does C have a pointer?
    typedef typename CombineTypeFuncs<c, boost::remove_pointer>::type c_pointer;
    typedef typename CombineTypeFuncs<y, boost::add_pointer>::type    y_pointer;
    typedef typename boost::conditional< boost::is_pointer<c>::value &&  boost::is_same<c_pointer,x>::value, y_pointer, Nil>::type type1;

    // is C const?
    typedef typename CombineTypeFuncs<c, boost::remove_const>::type  c_const;
    typedef typename CombineTypeFuncs<y, boost::add_const>::type     y_const;
    typedef typename boost::conditional< boost::is_const<c>::value && boost::is_same<c_const,x>::value, y_const, Nil>::type type2;

    // is C a reference?
    typedef typename CombineTypeFuncs<c, boost::remove_reference>::type  c_reference;
    typedef typename CombineTypeFuncs<y, boost::add_reference>::type      y_reference;
    typedef typename boost::conditional< boost::is_reference<c>::value && boost::is_same<c_reference,x>::value, y_reference, Nil>::type type3;

    
    // Search types type0, type1, ..., top find the first Not Nil!
    typedef typename FirstNotNil<type0, type1, type2, type3>::type type;
    
    // recursive
    typedef typename boost::conditional<boost::is_pointer<c>::value, typename replace_type<c_pointer, x,y>::type, Nil>::type type4;
        // add pointer if it had pointer:
        typedef typename boost::conditional<! boost::is_same<type4, Nil>::value, typename boost::add_pointer<type4>::type, Nil>::type next_type4;
    
    typedef typename boost::conditional<boost::is_const<c>::value, typename replace_type<c_const, x,y>::type, Nil>::type type5;
        // add const if it had const:
        typedef typename boost::conditional<! boost::is_same<type5, Nil>::value, typename boost::add_const<type5>::type, Nil>::type next_type5;

    typedef typename boost::conditional<boost::is_reference<c>::value, typename replace_type<c_reference, x,y>::type, Nil>::type type6;
        // add const if it had reference:
        typedef typename boost::conditional<! boost::is_same<type6, Nil>::value, typename boost::add_reference<type6>::type, Nil>::type next_type6;

    
    
    typedef typename FirstNotNil<type0, type1, type2, type3, type4, type5, type6>::type not_nil;
    typedef typename FirstNotNil<type0, type1, type2, type3, next_type4, next_type5, next_type6>::type recursive_type;
};

namespace JD_exclude {
    /////////// Compile time stack////////
    template<typename, typename>
    struct push {};
    
    
    template<typename T, typename...Ts, template< typename...> class TT>
    struct push<T, TT<Ts...>>
    {
        using type = TT<T, Ts...>;
        using element  = T;
    };
    
    
    //template<typename T, typename...Ts, template< typename...> class TT>
    //struct push<T>
    //{
    //    using type = TT<>;
    //};
    
    
    
    template<typename, typename>
    struct pop {};
    
    template<typename T, typename...Ts, template< typename...> class TT>
    struct pop<T, TT<Ts...>>
    {
        using type = TT<Ts...>;
        using element = T;
    };
    
    
    template< template< typename...> class TT, typename...Ts>
    struct stack
    {
        using type = TT<Ts...>;
    };
    
    
    void useStack()
    {
        //typedef typename stack<boost::add_const,int, float>::type Stack;
        
        //typedef typename push<int, std::tuple>::type NextStack;
        
        
    }
    
}

template<typename C>
struct replace
{
    typedef typename replace_type<C, bool, int>::type0 Type0;
    typedef typename replace_type<C, bool, int>::type1 Type1;
    typedef typename replace_type<C, bool, int>::type2 Type2;
    typedef typename replace_type<C, bool, int>::type3 Type3;
    //typedef typename replace_type<C, bool, int>::type4 Type4;
    typedef typename replace_type<C, bool, int>::not_nil    not_nil;
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    //constexpr auto x = sizeof(int);
    
    std::cout << std::boolalpha;
    
    JD::doReplace_type();
    
    TypeFuncList::useType();
    
    typedef typename FirstNotNil<Nil, char, int, bool>::type FNN;
    
    std::cout << typeid(FNN).name() <<  " " <<  typeid(Nil).name()  << std::endl;
    
    
    using C = bool const&;  //bool&; //bool const; // ==> int const*
    
    typedef replace_type<C, bool const, double> Base;
    
    typedef Base::type0             c_type0;
    typedef Base::type1             c_type1;
    typedef Base::type2             c_type2;
    typedef Base::type3             c_type3;
    typedef Base::type              c_type;
    typedef Base::not_nil           c_not_nil;
    typedef Base::recursive_type    c_recursive;
    
    std::cout << "C: " << typeid(C).name() << std::endl;
    
    std::cout << "Type0: " << typeid(c_type0).name() << std::endl;
    std::cout << "Type1: " << typeid(c_type1).name() << std::endl;
    std::cout << "Type2: " << typeid(c_type2).name() << std::endl;
    std::cout << "Type3: " << typeid(c_type3).name() << std::endl;
    std::cout << "Type: " << typeid(c_type).name() << std::endl;
    std::cout << "not_nil: " << typeid(c_not_nil).name() << std::endl;
    std::cout << "c_recursive: " << typeid(c_recursive).name() << std::endl;
    
    std::cout << std::is_same<double &, c_recursive>::value << std::endl;
    
    //c_not_nil c {};
    
    typedef typename replace_type<C, bool, int>::type0 Type0;
    
    std::cout << "Type0 is: " << boost::is_same<Nil, Type0>::value << "\n";
    
    typedef typename replace_type<C, bool, int>::not_nil NotNil;
    
    //NotNil nn{};
    
    std::cout << "NotNill is: " << boost::is_same<Nil, NotNil>::value << typeid(NotNil).name()   << "\n";
    
    typedef typename boost::remove_const<C>::type C_minus_const;
    typedef typename boost::remove_pointer<C_minus_const>::type C_minus_ptr_minus_const;
    
    std::cout << boost::is_same<C_minus_ptr_minus_const, bool>::value << std::endl;
    
    typedef typename CombineTypeFuncs<bool const*, boost::remove_const, boost::remove_pointer>::type Plain;
    
    Plain p {};
    
    std::cout << p <<  " Plain is bool: " << boost::is_same<Plain, bool>::value << std::endl;
    
    typedef typename CombineTypeFuncs<Plain, boost::add_pointer, boost::add_const>::type PlainRestored;
    
    PlainRestored pr{};
    
    std::cout << pr <<  " PlainRestored is bool const*: " << boost::is_same<PlainRestored, bool const *>::value << std::endl;
    
    bool is_fund = boost::is_fundamental<void const>::value; 
    
    bool same = replace_type<void*, void, int>::stripped_are_same;
    
    typedef typename replace_type<void*, void, int>::type t;
    
    t aT  = nullptr;
    
    std::cout << boost::is_same<t, int*>::value  << " "  << typeid(t).name() <<  std::endl;
    
    
    constexpr auto v_1 = dim_count<int,0>::value;
    constexpr auto v_2 = Dimension<int>::value;
    
    constexpr auto val0 = dim_count<int[8][2], 0>::value;
    constexpr auto val00 = Dimension<int[8][2]>::value;
    
    std::cout << val0 << " " << val00 <<    "\n";
    
    add_dim<int, val0>::array ar;
    
    add_dim<int[2], 4>::array another;
    
    
    auto val1 = dim_count<int[8][2], 1>::value;
    
    std::cout << val1 << "\n";

    auto val2 = dim_count<int[8][2], 2>::value;
    
    std::cout << val2 << "\n";

    return 0;
}

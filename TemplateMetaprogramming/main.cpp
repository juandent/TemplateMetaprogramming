//
//  main.cpp
//  TemplateMetaprogramming
//
//  Created by Juan Dent on 19/August/16.
//  Copyright © 2016 Juan Dent. All rights reserved.
//
#include "stdafx.h"

#include "exercise_3_1.hpp"
#include "Exercise 2_3.hpp"
#include "Exercise 2_3_JLBorges.hpp"
#include "AssociativeSequences.h"
#include "SequenceClasses.h"
#include "Chapter6.h"
#include "ExpressionTemplates_Ch_10.h"
#include "Exercises_4.hpp"


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
    typedef T type[Num];
};

template<typename T>
struct add_dim<T,0>
{
    typedef T  type;
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
	typedef C type;	// ? only to silence compiler warning in next function template
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
/* &doReplace_type& */
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
        
        typedef std::remove_pointer<C>::type c_pointer;
        typedef std::remove_const<c_pointer>::type c_pointer_const;
        
        cout << std::is_same<C, c_pointer>::value << endl;
        cout << std::is_same<C, c_pointer_const>::value << endl;
    
        
        c_pointer c = true;
        c_pointer_const cc =  false;
        
        cout << typeid(C).name() << endl;
        cout << typeid(c_pointer).name() << endl;
        cout << typeid(c_pointer_const).name() << endl;
        
        typedef  BaseType2::Remove<std::remove_const, std::remove_pointer>::c_type C_Type;
        typedef  BaseType2::Add<std::add_pointer, std::add_const>::y_type Y_Type;
        
        cout << std::is_same<C_Type, X>::value << endl;
        
        typedef  BaseType2::Result<C_Type, Y_Type>::type ReturnType;
        
        std::cout << typeid(ReturnType).name() << std::endl;

        
    }
    
}




namespace  TypeFuncList {    
    
    template< template <typename > class ...TypeFuncs >
    struct TypeFuncList
    {
        using type = TypeFuncList<TypeFuncs...>;
    };
    
/* &useTypeFuncList& */
    void useTypeFuncList()
    {
        typedef  TypeFuncList<boost::remove_const, boost::remove_pointer, boost::remove_bounds>::type Removers;
        typedef  TypeFuncList<boost::add_pointer, boost::remove_pointer, boost::remove_bounds>::type Adders;
    }
    
    template<typename ...Ts>
    struct Type 
    {
        using type = Type<Ts...>;
    };
    
/* &useType& */
    void useType()
    {
        typedef  Type<int, bool, char>::type Integrals;
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

namespace older
{
    
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
        
        // is C an array?
        typedef typename CombineTypeFuncs<c, boost::remove_bounds>::type  c_bounds;
        typedef  typename add_dim<y, dim_count<c,0>::value>::type          y_bounds;
        typedef typename boost::conditional<boost::is_array<c>::value && boost::is_same<c_bounds,x>::value, y_bounds, Nil>::type type4;
        
        
        // Search types type0, type1, ..., top find the first Not Nil!
        typedef typename FirstNotNil<type0, type1, type2, type3, type4>::type type;
        
        
        // recursive
        typedef typename boost::conditional<boost::is_pointer<c>::value, typename replace_type<c_pointer, x,y>::type, Nil>::type type10;
        // add pointer if it had pointer:
        typedef typename boost::conditional<! boost::is_same<type10, Nil>::value, typename boost::add_pointer<type10>::type, Nil>::type next_type10;
        
        typedef typename boost::conditional<boost::is_const<c>::value, typename replace_type<c_const, x,y>::type, Nil>::type type11;
        // add const if it had const:
        typedef typename boost::conditional<! boost::is_same<type11, Nil>::value, typename boost::add_const<type11>::type, Nil>::type next_type11;
        
        typedef typename boost::conditional<boost::is_reference<c>::value, typename replace_type<c_reference, x,y>::type, Nil>::type type12;
        // add const if it had reference:
        typedef typename boost::conditional<! boost::is_same<type12, Nil>::value, typename boost::add_reference<type12>::type, Nil>::type next_type12;
        
        typedef typename boost::conditional<boost::is_array<c>::value, typename replace_type<c_bounds, x,y>::type, Nil>::type type13;
        // add array if it had array:
        typedef typename boost::conditional<! boost::is_same<type13, Nil>::value, typename add_dim<type13, dim_count<c, 0>::value>::type, Nil>::type next_type13;
        
        
        typedef typename FirstNotNil<type0, type1, type2, type3, type4, type10, type11, type12, type13>::type not_nil;
        typedef typename FirstNotNil<type0, type1, type2, type3, type4, next_type10, next_type11, next_type12, next_type13>::type recursive_type;
        typedef typename boost::conditional<boost::is_same<recursive_type,Nil>::value, c, recursive_type>::type result_type;
    };
    
}


namespace AndyProwl
{
    template<typename, typename>
    struct append_to_type_seq { };
    
    template<typename T, typename... Ts, template<typename...> class TT>
    struct append_to_type_seq<T, TT<Ts...>>
    {
        using type = TT<Ts..., T>;
    };
    
    template<typename T, unsigned int N, template<typename...> class TT>
    struct repeat
    {
        using type = typename
        append_to_type_seq<
        T,
        typename repeat<T, N-1, TT>::type
        >::type;
    };
    
    template<typename T, template<typename...> class TT>
    struct repeat<T, 0, TT>
    {
        using type = TT<>;
    };
    
    
    template<typename... Ts>
    struct X { };
    
/* &useRepeat& */
    void useRepeat()
    {
        repeat<double, 5, std::tuple>::type t = std::make_tuple(1., 2., 3., 4., 5.);
        static_assert(
                      std::is_same<
                      decltype(t),
                      std::tuple<double, double, double, double, double>
                      >::value, "!");
        
        repeat<double, 3, X>::type y;
        static_assert(
                      std::is_same<decltype(y), X<double, double, double>>::value, "!");
    }
}

namespace LucDanton
{
    template<typename Dependent, std::size_t Index>
    using DependOn = Dependent;
    
    template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
    struct repeat;
    
    template<typename T, std::size_t N, std::size_t... Indices>
    struct repeat<T, N, std::index_sequence<Indices...>> {
        using type = std::tuple<DependOn<T, Indices>...>;
    };

/* &useRepeat& */
    void useRepeat()
    {
        repeat<int, 10>::type rep;
        static_assert( std::is_same<decltype(rep), std::tuple<int,int,int,int,int,int,int,int,int,int>>::value, "!");
        
        std::integer_sequence<int, 4>::value_type x{};
        
    }
}

    
    // Convert array into a tuple
    template<typename Array, std::size_t... I>
    decltype(auto) a2t_impl(const Array& a, std::index_sequence<I...>)
    {
        return std::make_tuple(a[I]...);
    }
    
    template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
    decltype(auto) a2t(const std::array<T, N>& a)
    {
        return a2t_impl(a, Indices());
    }
    
    // pretty-print a tuple (from http://stackoverflow.com/a/6245777/273767)
    
    template<class Ch, class Tr, class Tuple, std::size_t... Is>
    void print_tuple_impl(std::basic_ostream<Ch,Tr>& os,
                          const Tuple & t,
                          std::index_sequence<Is...>)
    {
        using swallow = int[]; // guaranties left to right order
        (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
    }
    
    template<class Ch, class Tr, class... Args>
    decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os,
                              const std::tuple<Args...>& t)
    {
        os << "(";
        print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
        return os << ")";
    }
    
/* &useSequence& */
    void useSequence()
    {
        std::array<int, 4> arr = {1,2,3,4};
        
        // convert an array into a tuple
        auto tup = a2t(arr);
        static_assert(std::is_same<decltype(tup),
                      std::tuple<int, int, int, int>>::value, "");
        
        // print it to cout
        std::cout << tup << '\n';
        
		std::make_index_sequence<3>::value_type val{ 5 };
        std::cout << val << std::endl;
        
    }

template<typename Func, typename Tup, std::size_t... index>
decltype(auto) invoke_helper(Func&& func, Tup&& tup, std::index_sequence<index...>)
{
    return func(std::get<index>(std::forward<Tup>(tup))...);
}

template<typename Func, typename Tup>
decltype(auto) invoke(Func&& func, Tup&& tup)
{
    constexpr auto Size = std::tuple_size<typename std::decay<Tup>::type>::value;
    return invoke_helper(std::forward<Func>(func), std::forward<Tup>(tup), std::make_index_sequence<Size>{});
}

/* &foo& */
void foo(int a, const std::string& b, float c)
{
    std::cout << a << " , " << b << " , " << c << '\n';
}

/* &useFoo& */
void  useFoo()
{
    auto args = std::make_tuple(2, "Hello", 3.5);
    invoke(foo, args);
}


namespace JD
{
    template<typename, typename>
    struct append_to_type_seq { };
    
    template<typename T, typename... Ts, template<typename...> class TT>
    struct append_to_type_seq<T, TT<Ts...>>
    {
        using type = TT<Ts..., T>;
    };

    // C++ Template Metaprogramming
    namespace Solution_to_Exercise_2_1 // FINAL SOLUTION to replace_type
    {
        template<typename c, typename x, typename y>
        struct replace_type;
        
        // C == X
        template <typename c, typename y>
        struct replace_type<c,c,y>
        {
            using type = y;
        };
        
        // C == X + const
        template <typename c, typename y>
        struct replace_type<c const,c,y>
        {
            using type = typename boost::add_const<y>::type;
        };
        
        // C == X + pointer
        template <typename c, typename y>
        struct replace_type<c*,c,y>
        {
            using type = typename boost::add_pointer<y>::type;
        };

        // C == X + pointer + pointer
        template <typename c, typename y>
        struct replace_type<c**,c,y>
        {
            using type = typename boost::add_pointer<typename replace_type<c*,c,y>::type>::type; 
        };

        // C == X + pointer + pointer + const
        template <typename c, typename y>
        struct replace_type<c**const,c,y>
        {
            using type = typename boost::add_const<typename replace_type<c**,c,y>::type>::type; 
        };

        // C = X + pointer + const
        template <typename c, typename y>
        struct replace_type<c* const,c,y>
        {
            using type = typename boost::add_const<typename replace_type<c*,c,y>::type>::type; 
        };

        // C = X + const + pointer
        template <typename c, typename y>
        struct replace_type<c const*,c,y>
        {
            using type = typename boost::add_pointer<typename replace_type<c const,c,y>::type>::type; 
        };

        
        template<typename Element, size_t N>
        struct add_dim
        {
            using type = Element[N];
        };
        
        // C == X + [N]
        template <typename c, size_t N, typename y>
        struct replace_type<c[N],c,y>
        {
            using type = typename add_dim<y, N>::type;
        };
        
        // C == X + pointer + [N]
        template <typename c, size_t N, typename y>
        struct replace_type<c*[N],c,y>
        {
            using type = typename add_dim< typename replace_type<c*,c,y>::type, N>::type;
        };
        
        // C == X + pointer + pointer + [N]
        template <typename c, size_t N, typename y>
        struct replace_type<c**[N],c,y>
        {
            using type = typename add_dim< typename replace_type<c**,c,y>::type, N>::type;
        };

        // C == X + reference
        template <typename c, typename y>
        struct replace_type<c&,c,y>
        {
            using type = typename boost::add_reference<y>::type;
        };

        // C == X + rvalue reference
        template <typename c, typename y>
        struct replace_type<c&&,c,y>
        {
            using type = typename boost::add_rvalue_reference<y>::type;
        };

        // C == X + reference + const
        template <typename c, typename y>
        struct replace_type<c const &,c,y>
        {
            using type = typename boost::add_const<typename replace_type<c&,c,y>::type>::type;
        };
        
        // C == X + reference + pointer
        template <typename c, typename y>
        struct replace_type<c*&,c,y>
        {
            using type = typename boost::add_reference<typename boost::add_pointer<y>::type>::type;
        };
        

        // C == X F ()
        template <typename c, typename y>
        struct replace_type<c(),c,y>
        {
            using type = y(*)();
        };
        
        // C == X& F (X&)
        template <typename c, typename y>
        struct replace_type<c&(c&),c,y>
        {
            using type = y&(*)(y&);
        };
        
        template<typename c>
        struct traits
        {
            static constexpr bool is_pointer = boost::is_pointer<c>::value;
            static constexpr bool is_const = boost::is_const<c>::value;
            static constexpr bool is_reference = boost::is_reference<c>::value;
            static constexpr bool is_array = boost::is_array<c>::value;
            
        };
        
/* &func& */
        int func()
        {
            return 1;
        }

/* &is_it& */
        bool is_it()
        {
            return true;
        }
        
/* &another& */
        int another()
        {
            return 1;
        }
/* &aBool& */
        bool& aBool(bool& a) {
            return a;
        }
/* &an& */
        int& an(int& y)
        {
            return y;
        }
/* &useReplaceType& */
        void useReplaceType()
        {
            using namespace std;
         
            cout << boolalpha;
            
            cout << "bool* const ==> int* const: " << is_same<typename replace_type<bool*const, bool, int>::type, int* const>::value << endl;
            
            cout << "bool* [30] ==> int* [30]: " << is_same<typename replace_type<bool*[30], bool, int>::type, int* [30]>::value << endl;
            
            cout << "char *& ==> int&: " << is_same<typename replace_type<char *&, char*, int>::type, int&>::value << endl;
            
            replace_type<decltype(is_it), bool, int>::type f = another;
            cout << f() << endl;
            
            replace_type<decltype(aBool), bool, int>::type g = an;
            int v = 45;
            cout << g(v) << endl;
            
            using CC = bool * const;
            using CC_replace = replace_type<CC, bool, int>;
            
            
            using new_type = CC_replace::type;
            
            new_type t = nullptr;
            
            replace_type<bool**const, bool, int>::type x = nullptr;
            
            replace_type<bool&&, bool, int>::type y  = func();
            int&& yy = func();
            
            int m = 4;
            int* pm = &m;
            replace_type<bool const&, bool const, int>::type dd = m;
            
            int*& pp = pm;
            
            cout << traits<bool*&>::is_reference;
            cout << traits<bool*&>::is_pointer;
            cout << endl;
            
            replace_type<bool*&, bool, int>::type p = pm;
            
            //replace_type<bool*&, bool, int>::type z = 5;
            
            typedef  FirstNotNil<Nil, char, int, bool>::type FNN;
            
            std::cout << typeid(FNN).name() <<  " " <<  typeid(Nil).name()  << std::endl;
            
#if 0            
            using C = bool ***; // NO: bool **[4];  //NO: bool const*[3]; //bool *[3]; // bool const&;  //bool&; //bool const; // ==> int const*
            
            cout << boost::is_array<C>::value << endl;
            
            cout << boost::is_pointer<typename boost::remove_bounds<C>::type>::value << endl;
            
            cout << boost::is_const<typename boost::remove_pointer<typename boost::remove_bounds<C>::type>::type>::value << endl;
            
            
            typedef replace_type<C, bool, double> Base;
            
            typedef Base::type0             c_type0;
            typedef Base::type1             c_type1;
            typedef Base::type2             c_type2;
            typedef Base::type3             c_type3;
            typedef Base::type4             c_type4;
            typedef Base::type              c_type;
            typedef Base::not_nil           c_not_nil;
            typedef Base::recursive_type    c_recursive;
            typedef Base::result_type       c_result;
            
            std::cout << "C: " << typeid(C).name() << std::endl;
            
            std::cout << "Type0: " << typeid(c_type0).name() << std::endl;
            std::cout << "Type1: " << typeid(c_type1).name() << std::endl;
            std::cout << "Type2: " << typeid(c_type2).name() << std::endl;
            std::cout << "Type3: " << typeid(c_type3).name() << std::endl;
            std::cout << "Type4: " << typeid(c_type4).name() << std::endl;
            std::cout << "Result type: " << typeid(c_result).name() << std::endl;
            std::cout << "Type: " << typeid(c_type).name() << std::endl;
            std::cout << "not_nil: " << typeid(c_not_nil).name() << std::endl;
            std::cout << "c_recursive: " << typeid(c_recursive).name() << std::endl;
            
            std::cout << std::is_same<double **, c_result>::value << std::endl;
#endif
        }
        // C++ Template Metaprogramming
        namespace Solution_to_Exercise_3_0 // 
        {
            template <unsigned long N>
            struct binary
            {
                static unsigned long constexpr value = binary<N/10>::value * 2 + N%10;
                BOOST_STATIC_ASSERT(N%10 < 2);
            };
            template<>
            struct binary<0>
            {
                static unsigned long constexpr value = 0;
            };
            
/* &useBinary& */
            void useBinary()
            {
                using namespace std;
                binary<1001> x;
                cout << x.value << endl;
                //binary<105> y; ==> triggers boost static assert
                
            }
        }
    }
    
    template<typename c, typename x, typename y>    // TT holds all the types produced byt this template!
    struct replace_type
    {
        // decomposing C:
        
        // is C identical to X?
        typedef typename boost::conditional< boost::is_same<c,x>::value, y, Nil>::type type0;
        
        // does C have a pointer?
        typedef typename boost::remove_pointer<c>::type c_pointer;
        typedef typename boost::add_pointer<y>::type    y_pointer;
        typedef typename boost::conditional< boost::is_pointer<c>::value &&  boost::is_same<c_pointer,x>::value, y_pointer, Nil>::type type1;
        
        //append_to_type_seq<type1, TT>
        // is C const?
        typedef typename boost::remove_const<c>::type  c_const;
        typedef typename boost::add_const<y>::type     y_const;
        typedef typename boost::conditional< boost::is_const<c>::value && boost::is_same<c_const,x>::value, y_const, Nil>::type type2;
        
        // is C a reference?
        typedef typename boost::remove_reference<c>::type  c_reference;
        typedef typename boost::add_reference<y>::type      y_reference;
        typedef typename boost::conditional< boost::is_reference<c>::value && boost::is_same<c_reference,x>::value, y_reference, Nil>::type type3;
        
        // is C an array?
        typedef typename boost::remove_bounds<c>::type              c_bounds;
        typedef typename add_dim<y, dim_count<c,0>::value>::type    y_bounds;
        typedef typename boost::conditional<boost::is_array<c>::value && boost::is_same<c_bounds,x>::value, y_bounds, Nil>::type type4;
        
        
        //append types to typelist
        //append_to_type_seq<type1, TT    >
        
        // Search types type0, type1, ..., top find the first Not Nil!
        typedef typename FirstNotNil<type0, type1, type2, type3, type4>::type type;
        
        
        // recursive
        typedef typename boost::conditional<boost::is_pointer<c>::value, typename replace_type<c_pointer, x,y>::type, Nil>::type type10;
        // add pointer if it had pointer:
        typedef typename boost::conditional<! boost::is_same<type10, Nil>::value, typename boost::add_pointer<type10>::type, Nil>::type next_type10;
        
        typedef typename boost::conditional<boost::is_const<c>::value, typename replace_type<c_const, x,y>::type, Nil>::type type11;
        // add const if it had const:
        typedef typename boost::conditional<! boost::is_same<type11, Nil>::value, typename boost::add_const<type11>::type, Nil>::type next_type11;
        
        typedef typename boost::conditional<boost::is_reference<c>::value, typename replace_type<c_reference, x,y>::type, Nil>::type type12;
        // add const if it had reference:
        typedef typename boost::conditional<! boost::is_same<type12, Nil>::value, typename boost::add_reference<type12>::type, Nil>::type next_type12;
        
        typedef typename boost::conditional<boost::is_array<c>::value, typename replace_type<c_bounds, x,y>::type, Nil>::type type13;
        // add array if it had array:
        typedef typename boost::conditional<! boost::is_same<type13, Nil>::value, typename add_dim<type13, dim_count<c, 0>::value>::type, Nil>::type next_type13;
        
        
        typedef typename FirstNotNil<type0, type1, type2, type3, type4, type10, type11, type12, type13>::type not_nil;
        typedef typename FirstNotNil<type0, type1, type2, type3, type4, next_type10, next_type11, next_type12, next_type13>::type recursive_type;
        typedef typename boost::conditional<boost::is_same<recursive_type,Nil>::value, c, recursive_type>::type result_type;
    };
/*
    template<typename c, typename x, typename y, template<typename...> class TT>    // TT holds all the types produced byt this template!
    struct replace_type<c,x,y,0,TT>
    {
        using type_col = TT<>;
        
    };
 */
}



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
    
    
/* &useStack& */
    void useStack()
    {
        //typedef typename stack<boost::add_const,int, float>::type Stack;
        
        //typedef typename push<int, std::tuple>::type NextStack;
        
        
    }
    
}


using namespace JD;

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

namespace JD { namespace Hide {
    
    template<typename T> struct iterator_traits;
    
    template<typename FwdIterator1, typename FwdIgterator2>
    void iter_swap( FwdIterator1 i, FwdIgterator2 j)
    {
        typename iterator_traits<FwdIterator1>::value_type * pi = &*i;
    }
    
    template<typename T, typename T::value_type>
    struct sqrt_impl
    {
        
    };
    constexpr double PI = 3.14159;
    template<class T>
    int f( T& x)
    {
        return x.template convert<3>(PI);
    }
    
    
    struct X
    {
        template<size_t T>
        int convert(const double d)
        {
            return d*PI;
        }
    };
/* &useF& */
    void useF()
    {
        auto x = X{};
        int r = f(x);
        
        std::cout << r << std::endl;
    }
    
    template<typename T>
    struct non_type_parameter
    {
        typedef T type;
    };
    
    template<
        class T
    ,   typename non_type_parameter<T>::type value = typename non_type_parameter<T>::type{}
    >
    struct initialized
    {
        static_assert( value > 0,"");
    };
    
/* &useInitialized& */
    void useInitialized()
    {
        typedef initialized<int, 10> Init;
    }
    
} }

using namespace std;

/* &person& */
class person 
{
public:
    person() = default;
    explicit person(const string& name) noexcept : name{name}  {}
    
/* &person.set_name& */
    void set_name(const string& n) { name = n; }
    string get_name() const { return name; }
    virtual void all_info() const noexcept { cout << "My name is " << name << endl; }
private:
        string name;
}/* #person# */;


        namespace Iterator_invalidation
        {
            template<typename T>
            class list_node;
            
            template <typename T>
            class half_list_node {
            public:
                half_list_node( list_node<T>* p) : next{p} {}
                list_node<T> *next;
            };
            
            template <typename T>
            class list_node : public half_list_node<T> {
            public:
                list_node( const T& d, list_node<T>* p) 
					: half_list_node<T>{ p }, data{ d }
				{}
                T data;
            };
            
           
            template <typename T>
            class forward_list_iterator{
                half_list_node<T> *current;
            public:
                forward_list_iterator( half_list_node<T>* p) : current{p}{}
                const T &operator*() const{
                    auto address = static_cast<list_node<T> *>(this->current);
                    assert( this->current == address);
                    return address->data;
                }
                void operator++(){
                    this->current = this->current->next;
                }
            };

            
            template <typename T>
            class forward_list{
            public:
                forward_list() {}
                half_list_node<T> before_first {nullptr};
                forward_list_iterator<T> before_begin() const {
                    return forward_list_iterator<T>{ const_cast<half_list_node<T>*>(&this->before_first)};
                }
                void insert( const T& t)
                {
                    auto existing_first = before_first.next;
                    auto node = new list_node<T>{t, existing_first};
                    before_first.next = node;
                }
            };
            
            
            void useForwardListIterator()
            {
                forward_list<int> fl;
                fl.insert(4);
                fl.insert(5);
                auto x = fl.before_begin();
                ++x;
                std::cout << (*x) << std::endl;
            }
        }
        
        
void testAssignmentOfIntToPointer();

namespace SpecialMemberFunctions
{
	void useSpecialMemberFunctions();
}

namespace Non_Type_Parameters
{
	void usePrint();
}

void useB7();

void useDXTM();

namespace Sqlpp11_Fragments
{
	void useSwallow();
}

namespace sqlpp
{
	void useIndexSequence();
	void useCharSequence();

}

namespace JD
{
	void useTypeSetJD();
}
/* &main& */
int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace std;

	JD::useTypeSetJD();

	sqlpp::useIndexSequence();

	sqlpp::useCharSequence();

	Sqlpp11_Fragments::useSwallow();

	useB7();

	useDXTM();

	Non_Type_Parameters::usePrint();

	SpecialMemberFunctions::useSpecialMemberFunctions();

	Exercise_4_3::Section_1::Original::call_next_if();

	testAssignmentOfIntToPointer();

	useExpressionTemplate();

	reverse_fold::useReverseFold();

	LambdaMetaFunction::useLambdaMetaFunction();

	Section6_3::useTransform();

	TinySequenceImplementation::useTiny();

	AssociativeSequences::Basics::usingOrder();

	Chapter3::Questions::Q3_8::useLength();

	Chapter3::Questions::Q3_1::useTransform();

	Chapter3::Questions::HigherOrderMetafunctions::useTwicePointerDouble();
    
    Iterator_invalidation::useForwardListIterator();
    
    
    solve_2_3();
    
    useType_Description();

    
    Solution_to_Exercise_3_7::solve_3_7();
    
    Chapter3::QuantityStuff::useQuantities();
    
    Solution_to_Exercise_3_3_AND_3_4::use_add_pointer();
    
    JD::Hide::useF();
    
    void** pv = nullptr;
    
    //constexpr auto x = sizeof(int);
    
    std::cout << std::boolalpha;

    Solution_to_Exercise_3_1::solve();
    
    Solution_to_Exercise_3_2::solve();
    
    JD::Solution_to_Exercise_2_1::useReplaceType();
    
    AndyProwl::useRepeat();
    
    useSequence();
    
    
    JD::doReplace_type();
    
    TypeFuncList::useType();
    
    typedef  FirstNotNil<Nil, char, int, bool>::type FNN;
    
    std::cout << typeid(FNN).name() <<  " " <<  typeid(Nil).name()  << std::endl;
    
    
    using C = bool ***; // NO: bool **[4];  //NO: bool const*[3]; //bool *[3]; // bool const&;  //bool&; //bool const; // ==> int const*
    
    cout << boost::is_array<C>::value << endl;
    
    cout << boost::is_pointer<typename boost::remove_bounds<C>::type>::value << endl;
    
    cout << boost::is_const<typename boost::remove_pointer<typename boost::remove_bounds<C>::type>::type>::value << endl;
    
    
    typedef replace_type<C, bool, double> Base;
    
    typedef Base::type0             c_type0;
    typedef Base::type1             c_type1;
    typedef Base::type2             c_type2;
    typedef Base::type3             c_type3;
    typedef Base::type4             c_type4;
    typedef Base::type              c_type;
    typedef Base::not_nil           c_not_nil;
    typedef Base::recursive_type    c_recursive;
    typedef Base::result_type       c_result;
    
    std::cout << "C: " << typeid(C).name() << std::endl;
    
    std::cout << "Type0: " << typeid(c_type0).name() << std::endl;
    std::cout << "Type1: " << typeid(c_type1).name() << std::endl;
    std::cout << "Type2: " << typeid(c_type2).name() << std::endl;
    std::cout << "Type3: " << typeid(c_type3).name() << std::endl;
    std::cout << "Type4: " << typeid(c_type4).name() << std::endl;
    std::cout << "Result type: " << typeid(c_result).name() << std::endl;
    std::cout << "Type: " << typeid(c_type).name() << std::endl;
    std::cout << "not_nil: " << typeid(c_not_nil).name() << std::endl;
    std::cout << "c_recursive: " << typeid(c_recursive).name() << std::endl;
    
    std::cout << std::is_same<double **, c_result>::value << std::endl;
    
    //c_not_nil c {};
    
    typedef  replace_type<C, bool, int>::type0 Type0;
    
    std::cout << "Type0 is: " << boost::is_same<Nil, Type0>::value << "\n";
    
    typedef  replace_type<C, bool, int>::not_nil NotNil;
    
    //NotNil nn{};
    
    std::cout << "NotNill is: " << boost::is_same<Nil, NotNil>::value << typeid(NotNil).name()   << "\n";
    
    typedef  boost::remove_const<C>::type C_minus_const;
    typedef  boost::remove_pointer<C_minus_const>::type C_minus_ptr_minus_const;
    
    std::cout << boost::is_same<C_minus_ptr_minus_const, bool>::value << std::endl;
    
    typedef  CombineTypeFuncs<bool const*, boost::remove_const, boost::remove_pointer>::type Plain;
    
    Plain p {};
    
    std::cout << p <<  " Plain is bool: " << boost::is_same<Plain, bool>::value << std::endl;
    
    typedef  CombineTypeFuncs<Plain, boost::add_pointer, boost::add_const>::type PlainRestored;
    
    PlainRestored pr{};
    
    std::cout << pr <<  " PlainRestored is bool const*: " << boost::is_same<PlainRestored, bool const *>::value << std::endl;
    
    bool is_fund = boost::is_fundamental<void const>::value; 
    
    //bool same = replace_type<void*, void, int>::stripped_are_same;
    
    typedef  replace_type<void*, void, int>::type t;
    
    t aT  = nullptr;
    
    std::cout << boost::is_same<t, int*>::value  << " "  << typeid(t).name() <<  std::endl;
    
    
    constexpr auto v_1 = dim_count<int,0>::value;
    constexpr auto v_2 = Dimension<int>::value;
    
    constexpr auto val0 = dim_count<int[8][2], 0>::value;
    constexpr auto val00 = Dimension<int[8][2]>::value;
    
    std::cout << val0 << " " << val00 <<    "\n";
    
    add_dim<int, val0>::type ar;
    
    add_dim<int[2], 4>::type another;
    
    
    auto val1 = dim_count<int[8][2], 1>::value;
    
    std::cout << val1 << "\n";

    auto val2 = dim_count<int[8][2], 2>::value;
    
    std::cout << val2 << "\n";

    return 0;
}

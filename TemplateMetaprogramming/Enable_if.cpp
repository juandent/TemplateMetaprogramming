#include "stdafx.h"

#include <type_traits>
#include <iostream>
using namespace std;



/// <summary>	pg 293
/// 			Programacion Generica en C++. </summary>

namespace NotUsingDefaultValues
{
	template<typename T, typename std::enable_if<(sizeof(T) > 2), int>::type a>
	T Add(T a, T b)
	{
		std::cout << "Large type" << std::endl;
		return a + b;
	}


	template<typename T, typename std::enable_if<(sizeof(T) <= 2), int>::type a>
	T Add(T a, T b)
	{
		std::cout << "Small type" << std::endl;
		return a + b;
	}


	void callAdd()
	{
		auto x = Add<long, 5>(123l, 560l);
		auto y = Add<char, 'i'>('a', 'b');
	}
}

namespace UsingDefaultValues
{
	template<typename T, typename std::enable_if<(sizeof(T) > 2), int>::type =0>
	T Add(T a, T b)
	{
		std::cout << "Large type" << std::endl;
		return a + b;
	}


	template<typename T, typename std::enable_if<(sizeof(T) <= 2), int>::type =0>
	T Add(T a, T b)
	{
		std::cout << "Small type" << std::endl;
		return a + b;
	}


	void callAdd()
	{
		auto x = Add(123l, 560l);
		auto y = Add('a', 'b');
	}
}

namespace UsingPointersWithDefaultValues
{
	template<typename T, typename std::enable_if<(sizeof(T) > 2)>::type* = nullptr>
	T Add(T a, T b)
	{
		std::cout << "Large type" << std::endl;
		return a + b;
	}


	template<typename T, typename std::enable_if<(sizeof(T) <= 2), int>::type* = nullptr>
	T Add(T a, T b)
	{
		std::cout << "Small type" << std::endl;
		return a + b;
	}


	void callAdd()
	{
		auto x = Add(123l, 560l);
		auto y = Add('a', 'b');
	}

}


namespace UsingEnableIfInParameters
{
	template<typename T>
	T Add(T a, T b, typename std::enable_if<(sizeof(T) > 2)>::type* = nullptr)
	{
		std::cout << "Large type" << std::endl;
		return a + b;
	}


	template<typename T>
	T Add(T a, T b, typename std::enable_if<(sizeof(T) <= 2), int>::type* = nullptr)
	{
		std::cout << "Small type" << std::endl;
		return a + b;
	}


	void callAdd()
	{
		auto x = Add(123l, 560l);
		auto y = Add('a', 'b');
	}

}

namespace UsingEnableIfInReturnValue
{
	template<typename T>
	typename std::enable_if<(sizeof(T) > 2), T>::type Add(T a, T b)
	{
		std::cout << "Large type" << std::endl;
		return a + b;
	}


	template<typename T>
	typename std::enable_if<(sizeof(T) <= 2), T>::type Add(T a, T b)
	{
		std::cout << "Small type" << std::endl;
		return a + b;
	}


	void callAdd()
	{
		auto x = Add(123l, 560l);
		auto y = Add('a', 'b');
	}

}

namespace ListaDeTipos
{

	template<typename...Tipos>
	struct Lista
	{};

	namespace detail
	{
		template<typename T1, typename T2>
		struct MismoTipo
		{
			static constexpr bool value = false;
		};

		template<typename T>
		struct MismoTipo<T,T>
		{
			static constexpr bool value = true;
		};
	}

	template< typename T, typename List>
	struct IndexOfType;

	template< typename T>
	struct IndexOfType<T, Lista<>>
	{
		static constexpr int value = 0;
	};

	template<typename T, typename Head, typename ...Tail>
	struct IndexOfType < T, Lista<Head, Tail...>>
	{
		static constexpr int value = detail::MismoTipo<T, Head>::value ? 0 : 
			1 + IndexOfType<T, Lista<Tail...>>::value;
	};

	void useIndexOfType()
	{
		using lista = Lista<double, float, unsigned int, std::vector<int>, int>;

		std::cout << "Indice de int: " << IndexOfType<int, lista>::value << std::endl;

		std::cout << "Indice de double: " << IndexOfType<double, lista>::value << std::endl;

		using lista_vacia = Lista<>;

		std::cout << "Indice de int: " << IndexOfType<int, lista_vacia>::value << std::endl;
	}


	template<int Index, typename Lista>
	struct TypeOfIndex;

	template<typename Head, typename ...Tail>
	struct TypeOfIndex<0, Lista<Head, Tail...>>
	{
		typedef Head type;
	};

	template<int Index, typename Head, typename...Tail> //, typename std::enable_if<(Index <= sizeof...(Tail)), int>::type = 0>
	struct TypeOfIndex<Index, Lista<Head, Tail...>>
	{
		typedef typename TypeOfIndex<Index - 1, Lista<Tail...>>::type type;
	};

	void usingTypeOfIndex()
	{
		using lista = Lista<int, double, char>;

		typedef TypeOfIndex<0, lista>::type first_type;

		typedef TypeOfIndex<1, lista>::type second_type;

		typedef TypeOfIndex<2, lista>::type third_type;

		using lista_vacia = Lista<>;

#if 0
		typedef TypeOfIndex<0, lista_vacia>::type first_type_in_empty_list;
#endif
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: SpecialMemberFunctions
//
// summary:	C++ Templates, 2nd edition.
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace SpecialMemberFunctions
{
	template<typename U>
	using NotIntegral = std::enable_if_t<!std::is_integral<U>::value>;

	template<typename T>
	class C
	{
	public:
		C() = default;

		C(C const volatile &) = delete;

		template<typename U, typename = NotIntegral<U> >
		C( C<U> const &) {
			std::cout << "tmpl copy ctor\n";
		}
	};

	void useSpecialMemberFunctions()
	{
		std::cout << "about to create a C\n";
		C<string> x;
		C<string> y{ x };
#if 0
		C<int> z;
		C<int> zz{ z };
#endif

	}
}
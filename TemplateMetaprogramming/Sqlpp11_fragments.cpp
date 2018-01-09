#include "stdafx.h"


struct Policy
{
	template<typename X>
	struct _base_t
	{
		struct _data_t
		{

		};
	};
};

#if 1

template<typename T>
void process(T& t)
{
	std::cout << t << std::endl;
}

template<typename ...Types>
struct operator_
{
	static int& _(Types... t)
	{
		using swallow = int[];
		(void)swallow {
			(process(t), 0)...
		};

		static int ret = 0;
		return ret;
	}
};

namespace sqlpp
{
	namespace detail
	{
		// A template that always returns false
		// To be used with static assert, for instance, to ensure it
		// fires only when the template is instantiated.
		template <typename... T>
		struct wrong
		{
			using type = std::false_type;
		};
	}  // namespace detail
	template <typename... T>
	using wrong_t = typename detail::wrong<T...>::type;


	//portable static assert
	struct name : std::false_type
	{
		template <typename... T>
		explicit name(T&&...)
		{
			static_assert(wrong_t<T...>::value, "portable static assert");
		}
		auto begin() const -> void;
		auto end() const -> void;
	};

	struct consistent_t : std::true_type
	{
		static void _() {};
	};

	struct inconsistent_t : std::false_type
	{
		static void _() {};
	};

	namespace detail
	{
		template <bool Consistent, typename Assert>
		struct static_check_impl
		{
			using type = Assert;
		};

		template <typename Assert>
		struct static_check_impl<true, Assert>
		{
			using type = consistent_t;
		};
	}  // namespace detail

	template <bool Consistent, typename Assert>
	using static_check_t = typename detail::static_check_impl<Consistent, Assert>::type;


	template<typename X>
	struct NoDefinition;

	namespace detail
	{
		template <typename... StaticChecks>
		struct static_combined_check_impl;

		// stops recursion:
		template <typename StaticCheck, typename... Rest>
		struct static_combined_check_impl<StaticCheck, Rest...>
		{
			using type = StaticCheck;
			//StaticCheck::_display_This;
		};
		// consistent_t is_a true_type!
		template <typename... Rest>
		struct static_combined_check_impl<consistent_t, Rest...>
		{
			using type = typename static_combined_check_impl<Rest...>::type;
			//NoDefinition<type>;
			//consistent_t::_display_This;
		};
		// stops recursion:
		template <>
		struct static_combined_check_impl<>
		{
			using type = consistent_t;
		};
	}  // namespace detail

	// returns true_type iif all StaticChecks are type consistent_t
	template <typename... StaticChecks>
	using static_combined_check_t = typename detail::static_combined_check_impl<StaticChecks...>::type;

	using combined = detail::static_combined_check_impl<consistent_t, inconsistent_t>::type;

	void implementation()
	{
#if 0
		static_combined_check_t<typename...Checks>;

		type t = nullptr;
		for (x : Checks)
		{
			if (x == consistent_t)
			{
				continue checking the rest;
			}
			else
			{
				t = x;
				break;
			}
		}
		if (t == nullptr)
		{
			t = consistent_t;
		}

		template <typename... Rest>
		struct static_combined_check_impl<consistent_t, Rest...>

#endif
}

}

namespace sqlpp
{
	template <typename Db = void, typename... Policies>
	struct statement_policies_t
	{
		using db = Db;
	};


	statement_policies_t<int, short, long>::db pol;
}

namespace sqlpp
{
	namespace detail
	{
		// Note: This is a minimalistic implementation of index_sequence available in C++14
		//       It should be replaced once the project is moved to C++14 or beyond
		template <std::size_t... Ints>
		struct index_sequence
		{
		};

		template <typename T, std::size_t N>
		struct make_index_sequence_impl;

		template <std::size_t N, std::size_t... Ints>
		struct make_index_sequence_impl<index_sequence<Ints...>, N>
		{
			using type = typename make_index_sequence_impl<index_sequence<Ints..., sizeof...(Ints)>, N - 1>::type;
		};

		template <std::size_t... Ints>
		struct make_index_sequence_impl<index_sequence<Ints...>, 0>
		{
			using type = index_sequence<Ints...>;
		};

		template <std::size_t N>
		using make_index_sequence = typename make_index_sequence_impl<index_sequence<>, N>::type;
	}  // namespace detail

	void useIndexSequence()
	{
		typedef detail::make_index_sequence_impl<detail::index_sequence<>, 4>::type seq4;
		seq4 aseq;
		(void)aseq;
		//auto x = aseq[1];

	}

	template <typename Context>
	std::integral_constant<char, '"'> get_quote_left(const Context&);

	template <typename Context>
	std::integral_constant<char, '"'> get_quote_right(const Context&);

	template <char... Cs>
	struct char_sequence
	{
		template <typename Context>
		static const char* char_ptr()
		{
			static char s[] = { Cs..., '\0' };
			return s;
		}
	};

	template <char... Cs>
	struct char_sequence<'!', Cs...>
	{
		template <typename Context>
		static const char* char_ptr()
		{
			static char s[] = { decltype(get_quote_left(std::declval<Context>()))::value, Cs...,
				decltype(get_quote_right(std::declval<Context>()))::value, '\0' };
			return s;
		}
	};

	template <std::size_t N, const char(&s)[N], typename T>
	struct make_char_sequence_impl;

	template <std::size_t N, const char(&s)[N], std::size_t... i>
	struct make_char_sequence_impl<N, s, sqlpp::detail::index_sequence<i...>>
	{
		using type = char_sequence<s[i]...>;
	};

	template <std::size_t N, const char(&Input)[N]>
	using make_char_sequence =
		typename make_char_sequence_impl<N, Input, sqlpp::detail::make_index_sequence<N - 1>>::type;

	struct _alias_t
	{
		static constexpr const char literal[] = "!hello";
		typedef make_char_sequence < sizeof(literal), literal> chSeq;

		static chSeq seq;
	};
	void useCharSequence()
	{
		_alias_t::chSeq ssss;
		auto s = _alias_t::chSeq::char_ptr<int>();
		//(void)seq;
		int i = 1;
	}

}

///////////////////////////////////////////////////////
// is_element_of => type_set (SIMPLER IMPL)
// how to find if a type T is a member of a type_set<typename...Elements>?
//		struct impl : Elements...
//		{};
//		template<typename T>
//		static constexpr bool count() {
//			return std::is_base_of<T, impl>::value;
//		}

namespace JD
{
	template<typename T>
	struct _base_t {};

	template<typename...Elements>
	struct type_set
	{
	//private:
		struct _impl : _base_t<Elements>...
		{
		};
	public:
		template<typename T>
		static constexpr bool count()
		{
			return std::is_base_of<_base_t<T>, _impl>::value;
		}
	};

	using myTypeSet = type_set<int, char, long>;


	void useTypeSetJD()
	{
		constexpr auto is_element = myTypeSet::count<float>();
		myTypeSet::_impl an_impl;
		int i = 0;
	}
}

namespace sqlpp
{
	namespace detail
	{
		template <typename E, typename SET>
		struct is_element_of;

		template <typename T>
		struct _base
		{
		};

		// A type set
		template <typename... Elements>
		struct type_set
		{
		private:
			struct _impl : _base<Elements>...
			{
			};

		public:
			using size = std::integral_constant<size_t, sizeof...(Elements)>;
			using _is_type_set = std::true_type;

			template <typename T>
			static constexpr bool count()
			{
				return std::is_base_of<_base<T>, _impl>::value;
			}

			template <typename T>
			struct insert
			{
				using type = typename std::conditional<count<T>(), type_set, type_set<T, Elements...>>::type;
			};

			template <template <typename A> class Predicate, typename T>
			struct insert_if
			{
				using type =
					typename std::conditional<Predicate<T>::value && !count<T>(), type_set<Elements..., T>, type_set>::type;
			};
		};

		template <typename E, typename SET>
		struct is_element_of
		{
			static_assert(wrong_t<is_element_of>::value, "SET has to be a type set");
		};

		template <typename E, typename... Elements>
		struct is_element_of<E, type_set<Elements...>>
		{
			static constexpr bool value = type_set<Elements...>::template count<E>();
		};
	}
}

#define SQLPP_VALUE_TRAIT_GENERATOR(name)                                                                   \
  namespace tag                                                                                             \
  {                                                                                                         \
    struct name;                                                                                            \
  }                                                                                                         \
  namespace detail                                                                                          \
  {                                                                                                         \
    template <typename T, typename Enable = void>                                                           \
    struct name##_impl                                                                                      \
    {                                                                                                       \
      using type = std::false_type;                                                                         \
    };                                                                                                      \
    template <typename T>                                                                                   \
    struct name##_impl<                                                                                     \
        T,                                                                                                  \
        typename std::enable_if<detail::is_element_of<tag::name, typename T::_traits::_tags>::value>::type> \
    {                                                                                                       \
      using type = std::true_type;                                                                          \
    };                                                                                                      \
  }                                                                                                         \
  template <typename T>                                                                                     \
  using name##_t = typename detail::name##_impl<T>::type;


#if 1
//   SQLPP_VALUE_TRAIT_GENERATOR(is_expression)
namespace sqlpp
{
	namespace tag
	{
		struct is_expression;
	}
	namespace detail
	{
		template<typename T, typename Enable = void>
		struct is_expression_impl
		{
			using type = std::false_type;
		};
		template<typename T>
		struct is_expression_impl<
			T,
			typename std::enable_if<detail::is_element_of<tag::is_expression, typename T::_traits::_tags>::value>::type>
		{
			using type = std::true_type;
		};
		template<typename T>
		using is_expression_t = typename detail::is_expression_impl<T>::type;

	}
}

#if 0
template <typename Table, typename... ColumnSpec>
struct table_t : public table_base_t, public ColumnSpec::_alias_t::template _member_t<column_t<Table, ColumnSpec>>...
#endif

#endif







#if 0

template <typename Context, typename Database, typename... Policies>
struct serializer_t<Context, statement_t<Database, Policies...>>
{
	using P = detail::statement_policies_t<Database, Policies...>;
	using _serialize_check = serialize_check_of<Context, typename Policies::template _base_t<P>::_data_t...>;
	using T = statement_t<Database, Policies...>;

	static Context& _(const T& t, Context& context)
	{
		using swallow = int[];
		(void)swallow {
			0,
				(serialize(static_cast<const typename Policies::template _base_t<P>&>(t)()._data, context), 0)...
	};

		return context;
}
};
#endif

namespace Sqlpp11_Fragments
{

	void useSwallow()
	{
		int x = 0;
		operator_<int, double, char*>::_(44, 5.77, "45");
	}
}
#else
template <typename Context, typename Database, typename... Policies>
struct serializer_t<Context, statement_t<Database, Policies...>>
{
	using P = detail::statement_policies_t<Database, Policies...>;
	using _serialize_check = serialize_check_of<Context, typename Policies::template _base_t<P>::_data_t...>;
	using T = statement_t<Database, Policies...>;

	static Context& _(const T& t, Context& context)
	{
		using swallow = int[];
		(void)swallow {
			0,
				(serialize(static_cast<const typename Policies::template _base_t<P>&>(t)()._data, context), 0)...
};

		return context;
	}
};

#endif

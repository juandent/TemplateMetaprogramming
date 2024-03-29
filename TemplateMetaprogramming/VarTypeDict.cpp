// #include "stdafx.h"

#include <iostream>
#include <type_traits>
#include <memory>

struct NullParameter;

namespace NSVarTypeDict
{
	template <size_t N, template<typename...> class TCont, typename...T>
	struct Create_
	{
		using type = typename Create_<N - 1, TCont, NullParameter, T...>::type;
	};
	template <template<typename...> class TCont, typename...T>
	struct Create_<0, TCont, T...>
	{
		using type = TCont<T...>;
	};
}

template<size_t N, typename T, typename Head, typename...Types>
struct Tag2ID_
{
	static constexpr bool is_same = std::is_same<T, Head>::value;
	static_assert(N == sizeof...(Types) + 1);

	static constexpr size_t position = is_same ? N -1 : Tag2ID_<N - 1, T, Types...>::position;
};

template<typename T, typename Head>
struct Tag2ID_<1, T, Head>
{
	static constexpr bool is_same = std::is_same<T, Head>::value;
	static constexpr int position = is_same ? 0 : -1;
};


template<typename T, typename ...Types>
constexpr size_t Tag2ID = Tag2ID_<sizeof...(Types), T, Types...>::position;

template<size_t Pos, typename...TTypes>
struct TypeAtPos;

template<size_t Pos, typename Type, typename...TTypes>
struct TypeAtPos<Pos,Type, TTypes...>
{
	using type = TypeAtPos<Pos - 1, TTypes...>::type;
};



template<typename Type, typename...Rest>
struct TypeAtPos<0, Type, Rest...>
{
	using type = Type;
};


template<typename TVal, size_t N, size_t M, typename TProcessedTypes, typename...TRemainingTypes>
struct ReplaceType_;

template<typename TVal, size_t N, size_t M, template<typename...> class TCont, typename ...TModifiedTypes, typename TCurType, typename... TRemainingTypes>
struct ReplaceType_<TVal, N, M, TCont<TModifiedTypes...>, TCurType, TRemainingTypes...>
{
	using type = typename ReplaceType_<TVal, N, M + 1, TCont<TModifiedTypes..., TCurType>, TRemainingTypes...>::type;
	// using type = typename ReplaceType_<TVal, N, M + 1, TCont<TRemainingTypes..., TCurType>, TModifiedTypes...>::type;
};


template<typename TVal, size_t N, template<typename...> class TCont, typename ...TModifiedTypes, typename TCurType, typename... TRemainingTypes>
struct ReplaceType_<TVal, N, N, TCont<TModifiedTypes...>, TCurType, TRemainingTypes...>
{
	using type = TCont<TModifiedTypes..., TVal, TRemainingTypes...>;
	// using type = TCont<TRemainingTypes..., TVal, TModifiedTypes...>;
};




template<typename TVal, size_t TagPos, typename TCont, typename ...TRemainingTypes>
using NewTupleType = typename ReplaceType_<TVal, TagPos, 0, TCont, TRemainingTypes...>::type;

// template<typename TVal, size_t TagPos, typename TCont, typename ...TRemainingTypes>
// struct NewTupleType : public ReplaceType_<TVal, TagPos, 0, TCont, TRemainingTypes...>
// {
// 	NewTupleType(auto x) {}
// };



template <typename ...TParameters>
struct VarTypeDict
{
	template<typename...TTypes>
	struct Values
	{
	private:
		std::shared_ptr<void> m_tuple[sizeof...(TTypes)];
		// static constexpr size_t Size = sizeof...(TTypes);
	public:
		Values() = default;
	// private:
		// template<> friend struct Values<TTypes...>;

		Values(std::shared_ptr<void>(&& input)[sizeof...(TTypes)])
		{
			for (size_t i = 0; i < sizeof...(TTypes); ++i)
			{
				m_tuple[i] = std::move(input[i]);
			}
		}
	public:
		template<typename TTag, typename TVal>
		auto Set(TVal&& val)&&
		{
			using namespace NSVarTypeDict;
			constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>;
			using rawVal = std::decay_t<TVal>;	// eliminate const, references, ...
			int pos = TagPos;
			rawVal* tmp = new rawVal(std::forward<TVal>(val));
			m_tuple[TagPos] = std::shared_ptr<void>(tmp, [](void* ptr)
				{
					rawVal* nptr = static_cast<rawVal*>(ptr);
					delete nptr;
				});
			size_t Size = sizeof...(TTypes);
			using new_type = NewTupleType<rawVal, TagPos, Values<>, TTypes...>;
			return new_type(std::move(m_tuple));
		}

		template <typename TTag>
		auto& Get() const
		{
			using namespace NSVarTypeDict;
			constexpr size_t TagPos = Tag2ID<TTag, TParameters...>;
			TTag* tt = nullptr;

			using type = typename TypeAtPos<TagPos, TTypes...>::type;
			int pos = TagPos;
			auto p = m_tuple[TagPos].get();
			type* t = static_cast<type*>(p);
			return *t;
		}
	};
	static auto Create()
	{
		using namespace NSVarTypeDict;
		using type = typename Create_<sizeof...(TParameters), Values > ::type;
		return type{};
	}

};



void useTag2ID()
{
	constexpr size_t pos= Tag2ID<long, int, long, char>;

	constexpr size_t pos2 = Tag2ID<long, int>;

	struct A; struct B; struct C;

	auto a = VarTypeDict<A, B, C>::Create().Set<A>(5).Set<B>(56L).Set<C>("hello").Get<C>();

}


struct X
{
	X() = default;
	X(std::shared_ptr<void>(&& input)[4])
	{
	}
	std::shared_ptr<void> m_tuple[4];
};


void useXX()
{
	X x;
	X y(std::move(x.m_tuple));
}
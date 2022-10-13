#include <algorithm>
#include <iostream>
#include <variant>
#include <array>


template<typename ConcreteItem>
class GlamourousItem
{
public:
	void appear_in_full_glory()
	{
		static_cast<ConcreteItem*>(this)->appear_in_full_glory();
	}
};

class PinkHeels : public GlamourousItem<PinkHeels>
{
public:
	void appear_in_full_glory()
	{
		std::cout << "Pink heels...\n";
	}
};

class GoldenMatch : public GlamourousItem<GoldenMatch>
{
public:
	void appear_in_full_glory()
	{
		std::cout << "Golden\n";
	}
};


template<typename...Args>
using PreciousItems = std::tuple<GlamourousItem<Args>...>;


constexpr auto glamourous_items = PreciousItems<PinkHeels, GoldenMatch>{};

constexpr auto items = std::tuple<GlamourousItem<PinkHeels>, GlamourousItem<GoldenMatch>>{};

auto fn = [] <typename... T> (GlamourousItem<T>...items)
{
	(items.appear_in_full_glory(), ...);
};


void call()
{
	std::apply([] <typename ...T>(GlamourousItem<T>...items)
	{
		(items.appear_in_full_glory(), ...);
	}, glamourous_items);

	// fn(glamourous_items);
	std::apply(fn, glamourous_items);

	std::apply(fn, items);
}


using GlamorousVariant = std::variant<PinkHeels, GoldenMatch>;


auto glamorousItems = std::array{ GlamorousVariant{ PinkHeels{} }, GlamorousVariant{ GoldenMatch{} } };

void useGI()
{
	call();

	for (auto& elem: glamorousItems)
	{
		std::visit([]<typename T> (GlamourousItem<T> item) {
			item.appear_in_full_glory();
		}, elem);
	}

	// fn<GoldenMatch, PinkHeels>( GoldenMatch{}, PinkHeels{});
}





namespace detail
{
	template<class F, class Tuple, std::size_t ...I>
	constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
	{
		return std::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
	};

	template<class F, class Tuple, class Idx>
	inline constexpr bool apply_is_noexcept = false;

	template<class F, class Tuple, std::size_t ...I>
	inline constexpr bool apply_is_noexcept<F, Tuple, std::index_sequence<I...>> = noexcept(std::invoke(std::declval<F>(), std::get<I>(std::declval<Tuple>())...));

}

template<class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t)
// noexcept( detail::apply_impl(F, Tuple, std::make_index_sequence<std::tuple_size_v<Tuple>>))
{
	return detail::apply_impl(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}



// std::invoke
namespace detail
{
	template<class>
	constexpr bool is_reference_wrapper_v = false;

	template<typename U>
	constexpr bool is_reference_wrapper_v<std::reference_wrapper<U>> = true;

	template<typename C, typename Pointed, typename T1, typename...Args >
	constexpr decltype(auto) invoke_memptr(Pointed C::*f, T1&& t1, Args&&...args)
	{
		if constexpr (std::is_function_v<Pointed>)
		{
			if constexpr (std::is_base_of_v<C, std::decay_t<T1>>)
			{
				return (std::forward<T1>(t1).*f)(std::forward<Args>(args)...);
			}
			else if constexpr (is_reference_wrapper_v<std::decay_t<T1>>)
			{
				return (t1.get().*f)(std::forward<Args>(args)...);
			}
			else
			{
				return (*std::forward<T1>(t1)).*f(std::forward<Args>(args)...);
			}
		}
		else
		{
			static_assert(std::is_object_v<Pointed> && sizeof...(Args) == 0);
			if constexpr (std::is_base_of_v<C, std::decay_t<T1>>)
			{
				return std::forward<T1>(t1).*f;
			}
			else if constexpr (is_reference_wrapper_v<std::decay_t<T1>>)
			{
				return t1.get().*f;
			}
			else
			{
				return (*std::forward<T1>(t1)).*f;
			}
		}
	}
}

template<typename F, typename ...Args>
constexpr auto  //std::invoke_result_t<F, Args...>
invoke(F&& f, Args&& ... args)  noexcept(std::is_nothrow_invocable_v<F, Args...>)
{
	if constexpr ( std::is_member_pointer_v<std::decay_t<F>>)
	{
		return detail::invoke_memptr(f, args...);
	}
	else
	{
		// return f(args...);
		return std::forward<F>(f)(std::forward<Args>(args)...);
	}
}



auto get_function()
{
	return [](int a, int b) 
	{
		return a + b;
	};
}
struct ABC
{
	std::reference_wrapper<int> wrapper;

	int value;

	double getter()
	{
		return 15.5;
	}


	int operator()(int a, int b) &&
	{
		return a + b;
	}
	int operator()(int a, int b) &
	{
		return a * b;
	}

	ABC(int num)  : wrapper{num}, value(num) {}
};

ABC  getABC()
{
	return ABC{5};
}

template<typename T> requires (!std::is_fundamental_v<T>)
constexpr bool is_base_of_itself = std::is_base_of_v<T, T>;

template<typename T>
using decayed = std::decay_t<T>;

void useInvoke()
{
	constexpr bool is = is_base_of_itself<ABC>;
	using dec = decayed<const  ABC&>;

	// auto res = get_function()(3, 7);

	auto abc = getABC();
	auto r = abc(3, 5);
	auto s = ABC{5}(3, 5);

	auto res = invoke(ABC{5}, 3, 7);
	auto rw = std::reference_wrapper<ABC>(abc);
	auto res2 = invoke( &ABC::getter, ABC{9});
}



namespace using_tuple
{
	template<typename ...Args>
	using PreciousItems = std::tuple<GlamourousItem<Args>...>;

	auto glamor_items = PreciousItems < PinkHeels, GoldenMatch >{} ; // a tuple!

	void use()
	{
		std::apply([]<typename ...T> (GlamourousItem<T>...items)
		{
			(items.appear_in_full_glory(), ...);
		}, glamor_items);
	
	}
}

namespace using_variant
{

	using integers = std::variant<short, int, long, long long>;

	auto arrs = std::array{ integers{short{}}, integers{int{}} };

	using GlamorousVariant = std::variant<PinkHeels, GoldenMatch>;

	auto obj = GlamorousVariant{ PinkHeels{} };
	auto obj2 = GlamorousVariant{ GoldenMatch{} };

	auto glamor_items = std::array{ obj, obj2 };


	void use()
	{
		for(auto& elem : glamor_items)
		{
			std::visit([] <typename T> (GlamourousItem<T> item)  {
				item.appear_in_full_glory();
			}, elem);
		}


		integers i { 5 };
		auto yy = std::get<int>(i);
	}

}

namespace using_wrap
{
	
	class CommonGlamorousItem
	{
		GlamorousVariant _item;
	public:
		template<typename T> requires std::is_base_of_v<GlamourousItem<T>, T>
		explicit CommonGlamorousItem(T&& item) : _item{ std::forward<T>(item) }
		{}
		void appear_in_full_glory()
		{
			std::visit([] <typename T> (GlamourousItem<T> item)
			{
				item.appear_in_full_glory();
			}, _item);
		}
	};

	auto glam_items = std::array{ CommonGlamorousItem{PinkHeels{}}, CommonGlamorousItem{GoldenMatch{}} };

	void use()
	{
		for(auto& elem: glam_items)
		{
			elem.appear_in_full_glory();
		}
	}

}


namespace  type_erasure_wrapper
{
	class TypeErasedItemBase
	{
	public:
		virtual ~TypeErasedItemBase() = default;
		virtual void appear_in_full_glory_impl() = 0;
	};

	template<typename T>   requires requires(T t)
	{
		t.appear_in_full_glory();
	}
	class TypeErasedItem final : public TypeErasedItemBase
	
	{
		T t_;
	public:
		explicit TypeErasedItem(T t)  : t_(std::move(t))
		{
		}
		void appear_in_full_glory_impl() override
		{
			t_.appear_in_full_glory();
		}
	};

	class GlamorousItem
	{
		std::unique_ptr<TypeErasedItemBase> item_;
	public:
		template<typename T>
		explicit GlamorousItem(T t) : item_{std::make_unique<TypeErasedItem<T>>(std::move(t))} {}
		void appear_in_full_glory() { item_->appear_in_full_glory_impl(); }
	};


	class PinkHeels
	{
	public:
		void appear_in_full_glory() { std::cout << "Pink high heels\n"; }
	};

	class GoldenWatch
	{
	public:
		void appear_in_full_glory() { std::cout << "GoldenWatch \n"; }
	};


	auto glam_items = std::array{ GlamorousItem{PinkHeels{}}, GlamorousItem{GoldenWatch{}} };


}

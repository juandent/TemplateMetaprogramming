#include <iostream>
#include <type_traits>
#include <memory>
#include <map>


namespace detail
{


	template<typename T>
	struct RemConstRef_;


	template<typename T>
	struct RemConstRef_<const T>
	{
		using type = T;
	};

	template<typename T>
	struct RemConstRef_<const  T&>
	{
		using type = T;
	};

	template<typename T>
	struct RemConstRef_<T&>
	{
		using type = T;
	};
}

template<typename T>
using RemConstRef = typename detail::RemConstRef_<T>::type;



#include <policies/policy_macro_begin.h>


#undef TypePolicyObj

#define TypePolicyObj(PolicyName, Ma, Mi, Val) \
struct PolicyName : virtual public Ma\
{ \
	using MajorClass = Ma;	\
    using MinorClass = Ma::Mi##TypeCate; \
    using Mi = MinorClass::Val; \
}






template<typename ...TPolicies>
struct PolicyContainer;


template<bool left, typename right>
constexpr bool AndValue = false;

template<typename right>
constexpr bool AndValue<true, right> = right::value;



namespace NSPolicySelect
{
	template<typename TPolicyContainer, typename  TMajorClass, typename ...TPolicies>
	struct MajorFilter_;

	template <typename MCO, typename TMajorClass, typename... TP>
	struct MajorFilter_
	{
		using type = MCO;
	};

	template <typename... TFilteredPolicies, typename TMajorClass, typename TCurPolicy, typename... TP>
	struct MajorFilter_<PolicyContainer<TFilteredPolicies...>, TMajorClass,	TCurPolicy, TP...>
	{
		template <typename CurMajor, typename TDummy = void>
		struct _impl
		{
			using type = typename MajorFilter_<PolicyContainer<TFilteredPolicies...>, TMajorClass, TP...>::type;
		};

		template <typename TDummy>
		struct _impl<TMajorClass, TDummy>
		{
			using type = typename MajorFilter_<PolicyContainer<TFilteredPolicies..., TCurPolicy>, TMajorClass, TP...>::type;
		};
		using type = typename _impl<typename TCurPolicy::MajorClass>::type;
	};


	template<typename MinorClass, typename...TP>
	struct MinorDedup_
	{
		static constexpr bool value = true;
	};

	template<typename TMinorClass, typename TCurPolicy, typename...TP>
	struct MinorDedup_<TMinorClass, TCurPolicy, TP...>
	{
		using TCurMirror = typename TCurPolicy::MinorClass;

		static constexpr bool cur_check = !(std::is_same_v<TMinorClass, TCurMirror>);

		static constexpr bool value = AndValue < cur_check, MinorDedup_<TMinorClass, TP...>>;
	};


	template<typename TPolicyCont>
	struct MinorCheck_
	{
		static constexpr bool value = true;
	};


	template<typename TCurPolicy, typename ... TP>
	struct MinorCheck_<PolicyContainer<TCurPolicy, TP...>>
	{
		static constexpr bool cur_check = MinorDedup_<typename TCurPolicy::MinorClass, TP...>::value;

		static constexpr bool value = AndValue<cur_check, MinorCheck_<PolicyContainer<TP...>>>;
	};




	template<typename ...TPolicies>
	constexpr bool IsArrayEmpty = false;

	template<>
	constexpr bool IsArrayEmpty<> = true;


	template<typename TPolicyCont>
	struct PolicySelRes;


	template<typename TPolicy>
	struct PolicySelRes< PolicyContainer<TPolicy>> : public TPolicy {};

	template<typename TCurPolicy, typename... TOtherPolicies>
	struct PolicySelRes< PolicyContainer<TCurPolicy, TOtherPolicies...>> : public TCurPolicy, public PolicySelRes<PolicyContainer<TOtherPolicies...>> {};


	template<typename TMajorClass, typename TPolicyContainer>
	struct Selector_;

	template<typename TMajorClass,typename ... TPolicies>
	struct Selector_<TMajorClass, PolicyContainer<TPolicies...>>
	{
		using TMF = typename MajorFilter_<PolicyContainer<>, TMajorClass, TPolicies...>::type;

		static_assert(MinorCheck_<TMF>::value, "Minor class conflict");

		using type = std::conditional_t<IsArrayEmpty<TMF>, TMajorClass, PolicySelRes<TMF>>;
	};

	template<typename TMajorClass >
	struct Selector_<TMajorClass, PolicyContainer<>>
	{
		using type = TMajorClass;
	};

}



struct AccPolicy
{
	using MajorClass = AccPolicy;

	struct AccuTypeCate
	{
		struct Add;
		struct Mul;
	};

	using Accu = AccuTypeCate::Mul;

	struct IsAveValueCate;
	static constexpr bool IsAve = false;

	struct ValueTypeCate;
	using Value = float;
};


#if 1


template<typename TMajorClass, typename TPolicyContainer>
using PolicySelect = typename NSPolicySelect::Selector_<TMajorClass, TPolicyContainer >::type;

template<typename ...T>
static constexpr bool DependencyFalse = false;



template<typename ...TPolicies>
struct Accumulator
{
	using TPoliCont = PolicyContainer<TPolicies...>;
	using TPolicyRes = PolicySelect<AccPolicy, TPoliCont>;

	using ValueType = typename TPolicyRes::Value;
	static constexpr bool is_ave = TPolicyRes::IsAve;
	using AccuType = typename TPolicyRes::Accu;

	template<typename TIn>
	static auto Eval(const TIn& in)
	{
		if constexpr (std::is_same_v<AccuType, AccPolicy::AccuTypeCate::Add>)
		{
			ValueType count = 0;
			ValueType res = 0;

			for(const auto&  x : in)
			{
				res += x;
				count += 1;
			}

			if constexpr (is_ave)
			{
				return res / count;
			}
			else
			{
				return res;
			}
		}
		else if constexpr (std::is_same_v<AccuType, AccPolicy::AccuTypeCate::Mul>)
		{
			ValueType count = 0;
			ValueType res = 1;

			for(const auto& x : in)
			{
				res *= x;
				++count;
			}

			if constexpr (is_ave)
			{
				return pow(res, 1.0 / count);
			}
			else
			{
				return res;
			}
		}
		else
		{
			static_assert(DependencyFalse<TPolicies...>);
		}
	}

};

#endif

TypePolicyObj(PAddAccu, AccPolicy, Accu, Add);
TypePolicyObj(PMulAccu, AccPolicy, Accu, Mul);
ValuePolicyObj(PAve, AccPolicy, IsAve, true);
ValuePolicyObj(PNoAve, AccPolicy, IsAve, false);
TypePolicyTemplate(PValueTypeIs, AccPolicy, Value);
ValuePolicyTemplate(PAvePolicyIs, AccPolicy, IsAve);


void useAcc()
{


	using t = typename PAddAccu::MinorClass::Add;

	static_assert(std::is_same<t, AccPolicy::AccuTypeCate::Add>::value);

	constexpr bool empty = NSPolicySelect::IsArrayEmpty<>;


	int a[] = { 1,2,3,4,5 };
	std::cout << Accumulator<PAddAccu>::Eval(a) << std::endl;
	std::cout << Accumulator<PAddAccu, PAvePolicyIs<true>>::Eval(a) << std::endl;
	Accumulator<>::ValueType* p;

	using rem = RemConstRef<const int&>;

}


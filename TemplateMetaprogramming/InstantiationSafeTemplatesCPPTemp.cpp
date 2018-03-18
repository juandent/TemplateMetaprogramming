#include "stdafx.h"


template<typename T1, typename T2>
class HasLess
{
	template<typename T> struct Identity;
	template<typename U1, typename U2>
	static std::true_type test(Identity<decltype(std::declval<U1>() < std::declval<U2>())>*);

	template<typename U1, typename U2>
	static std::false_type test(...);

public:
	static constexpr bool value = decltype(test<T1, T2>(nullptr))::value;

};


template<typename T1, typename T2, bool HasLess>
class LessResultImpl
{
public:
	using Type = decltype(std::declval<T1>() < std::declval<T2>());
};


template<typename T1, typename T2>
class LessResultImpl<T1,T2,false>
{};


template<typename T1, typename T2>
class LessResultT : public LessResultImpl<T1, T2, HasLess<T1, T2>::value>
{};

template<typename T1, typename T2>
using LessResult = typename LessResultT<T1, T2>::Type;

namespace FirstMin
{
	template<typename T>
	std::enable_if_t<std::is_convertible_v<LessResult<T const&, T const&>, bool>, T const&>
		min(T const& x, T const& y)
	{
		if (y < x)
			return y;
		return x;
	}
}

namespace TypeOverload
{

	struct X1 {};
	bool operator < (X1 const&, X1 const&) { return true; }

	struct X2 {};
	bool operator <(X2, X2) { return true; }

	struct X3 {};
	bool operator <(X3&, X3&) { return true; }

	struct X4 {};

	struct BoolConvertible
	{
		operator bool() const { return true; }
		operator int() const { return 1; }	//??????
		operator char*() const { return nullptr; }
	};

	struct X5 {};

	BoolConvertible operator <(X5 const&, X5 const&)
	{
		return BoolConvertible();	// which conversion operator is called?
	};

	struct NotBoolConvertible {};

	struct X6 {};

	NotBoolConvertible operator <(X6 const&, X6 const&)
	{
		return NotBoolConvertible();	// which conversion operator is called?
	};

	struct BoolLike
	{
		explicit operator bool() const { return true; }
	};

	struct X7 {};

	BoolLike operator<(X7 const&, X7 const&)
	{
		return BoolLike();
	}

	void main()
	{
		using namespace FirstMin;

		min(X1(), X1());	//ok
		min(X2(), X2());	//ok
		//min(X3(), X3());	//not ok
		//min(X4(), X4());	//not ok
		min(X5(), X5());	//ok
		//min(X6(), X6());	//not ok
		//min(X7(), X7());	//not ok
	}


}


namespace NotOverconstrained
{

	class HasBoolOperator
	{
	public:
		operator bool() const { return true; }
	};

	template<typename T>
	class IsContextualBoolT
	{
	public:
		template<typename T> struct Identity;

		template<typename U>
		static constexpr std::true_type test(Identity<decltype(std::declval<U>() ? 0 : 1)>* val = nullptr);
		
		template<typename U>
		static constexpr std::false_type test(...);
	public:
		static constexpr bool value = decltype(test<T>(nullptr))::value;
	};

	template<typename T>
	std::enable_if_t<IsContextualBoolT<LessResult<T const&, T const&>>::value, T const&>
	min(T const& x, T const& y)
	{
		if (y < x)
			return y;
		return x;
	}

	template<typename T> struct Identity;
	template<typename U>
	std::true_type test(Identity<decltype(std::declval<U>() ? 0 : 1)>* val = nullptr)
	{
		using tt = decltype(std::declval<U>());
		std::remove_reference_t< tt> * pt;
		return std::true_type{};
	}
	using t = decltype(IsContextualBoolT<int>::test<HasBoolOperator>(nullptr));

	void main()
	{
		auto r = test<HasBoolOperator>(nullptr);

		t* pT = nullptr;

		HasBoolOperator hbo;
		if (hbo)
		{
			auto eq = pT == nullptr;
			++pT;
		}

		using namespace TypeOverload;
		using NotOverconstrained::min;

		min(X1(), X1());	//ok
		min(X2(), X2());	//ok
							//min(X3(), X3());	//not ok
							//min(X4(), X4());	//not ok
		min(X5(), X5());	//ok
		//min(X6(), X6());	//ok
		min(X7(), X7());	//ok
	}
}



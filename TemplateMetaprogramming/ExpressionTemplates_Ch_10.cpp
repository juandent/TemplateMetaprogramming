#include "stdafx.h"
#include "ExpressionTemplates_Ch_10.h"

template<typename L, typename OpTag, typename R>
struct Expression
{
	Expression(L const& l, R const& r)
		: l{ l }, r{ r }
	{}

	float operator[](unsigned index) const
	{
		return OpTag::apply(l[index], r[index]);
	}

	L const& l;
	R const& r;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A plus: operation plus </summary>
///
/// <remarks>	Juan Dent, 31/3/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

struct plus
{
	static float apply(float a, float b)
	{
		return a + b;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A minus: operation minus </summary>
///
/// <remarks>	Juan Dent, 31/3/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

struct minus
{
	static float apply(float a, float b)
	{
		return a - b;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Addition operator for expressions </summary>
///
/// <remarks>	Juan Dent, 31/3/2017. </remarks>
///
/// <typeparam name="L">	Type of the l. </typeparam>
/// <typeparam name="R">	Type of the r. </typeparam>
/// <param name="l">	The const to process. </param>
/// <param name="r">	The const to process. </param>
///
/// <returns>	The result of the operation. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename L, typename R>
Expression<L, plus, R>
operator+(L const& l, R const& r)
{
	return Expression<L, plus, R>(l, r);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Subtraction operator for expressions </summary>
///
/// <remarks>	Juan Dent, 31/3/2017. </remarks>
///
/// <typeparam name="L">	Type of the l. </typeparam>
/// <typeparam name="R">	Type of the r. </typeparam>
/// <param name="l">	The const to process. </param>
/// <param name="r">	The const to process. </param>
///
/// <returns>	The result of the operation. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename L, typename R>
Expression<L, minus, R>
operator-(L const& l, R const& r)
{
	return Expression<L, minus, R>(l, r);
}


class Array : std::vector<float>
{
	template<typename L, typename OpTag, typename R>
	friend struct Expression;

public:
	using std::vector<float>::vector;

	template<typename Expr>
	Array& operator=(Expr const& x)
	{
		for (auto i = 0u; i < this->size(); ++i)
		{
			(*this)[i] = x[i];
		}
		return *this;
	}
};

void useExpressionTemplate()
{
	Array a{ 1,3,6,9 };
	Array b{ 2,4,12,11 };
	Array c{ 4,8,4,9 };
	auto x = (a + b)[1];
	auto y = (a + b + c)[1];
	Array z(4);
	z = a + b + c;
}

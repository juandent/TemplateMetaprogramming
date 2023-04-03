

#include <compare>
#include <concepts>
#include <functional>


template<typename T>
struct Value
{
	T val{};

	auto operator<=>(const Value& rhs) const noexcept(noexcept(val<=>val))
	{
		return std::compare_three_way{}(val, rhs.val);
	}
};


struct BB
{
	int num;

	bool operator==(const BB&) const = default;
	auto operator<=>(const BB& rhs) const noexcept -> std::strong_ordering
	{
		return num <=> rhs.num;
	}
};


void useValue()
{
	Value<BB> a{ 10 }, b{ 14 };
	bool less = a < b;

	constexpr bool x = std::three_way_comparable_with<BB, BB, std::partial_ordering>;

	//std::compare_three_way{}(a,b);


}

namespace inherit_protected
{
	struct Base
	{
	};

	struct Derived : Base
	{
		int i;
		bool operator==(const Derived& d) const
		{
			return i == d.i;
		}
	};

	void use()
	{
		Derived d1, d2;
		bool eq = d1 == d2;

	}
}
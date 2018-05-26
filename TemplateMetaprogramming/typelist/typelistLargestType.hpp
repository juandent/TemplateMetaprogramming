#pragma once

// LargestType

namespace LowLevel
{

	template<typename List>
	class LargestTypeT;


	template<typename List>
	class LargestTypeT
	{
	private:
		using First = Front<List>;
		using Rest = typename LargestTypeT< PopFront<List>>::Type;
	public:
		using Type = IfThenElse< sizeof(First) >= sizeof(Rest), First, Rest>;
	};

	template<>
	class LargestTypeT<Typelist<>>							// too low level hardwired empty definition
	{
	public:
		using Type = char;
	};

	template<typename List>
	using LargestType = typename LargestTypeT<List>::Type;

}

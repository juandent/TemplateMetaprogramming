#pragma once



template<typename T>
class Number
{
	T elem;
public:
	Number(const T& el) : elem(el ){}

	template<typename U=T, class = typename std::enable_if<std::is_integral<U>::value>::type>
	T simple_modulus(const U& o)
	{
		return elem % o;
	}

	template<typename U = T>	
	U operator%(const U& other)
	{
		if constexpr (std::is_floating_point<U>::value)
		{
			return std::fmod(elem, other);
		}
		else
		{
			return simple_modulus(other);
		}
	}
};
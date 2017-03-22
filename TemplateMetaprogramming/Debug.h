#pragma once

namespace Debug
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Format unit that comes as a std::ratio </summary>
	///
	/// <remarks>	Juan Dent, 16/3/2017. </remarks>
	///
	/// <typeparam name="Unit">	Type of the unit. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Ratio>
	inline std::string formatRatio()
	{
		std::ostringstream os{};
		os << Ratio::num << ":" << Ratio::den;
		auto s = os.str();
		return s;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Utility for debugging which outputs string to console </summary>
	///
	/// <remarks>	Juan Dent, 17/3/2017. </remarks>
	///
	/// <param name="title">	The title. </param>
	/// <param name="str">  	The string. </param>
	/// <param name="sep">  	(Optional) The separator. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	inline void output(const std::string&  title, const std::string& str, const std::string& sep = " = ")
	{
		std::cout << title << sep << str << std::endl;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A template declaration that is not defined on purpose! </summary>
	///
	/// <remarks>	Juan Dent, 17/3/2017. 
	/// 			Will print the type T on compilation
	/// 			</remarks>
	///
	/// <typeparam name="T">	Generic type parameter. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	struct TypeDecl;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A template declaration that is not defined on purpose!. </summary>
	///
	/// <remarks>	Juan Dent, 17/3/2017. 
	/// 			Will print the value of N on compilation
	/// 			</remarks>
	///
	/// <typeparam name="N">	Type of the n. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<int N>
	struct IntegralDecl;

}

//namespace Support
//{
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//	/// <summary>	A verify units. </summary>
//	///
//	/// <remarks>	Juan Dent, 16/3/2017. 
//	/// 			If pos x of the dimension is 0, then the 
//	/// 			corresponding unit must be unity (1:1)
//	/// 			</remarks>
//	///
//	/// <typeparam name="Dimension">	Type of the dimension. </typeparam>
//	/// <typeparam name="Units">		Type of the units. </typeparam>
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	template<typename Dimension, typename Units, size_t N>
//	struct verify_units
//	{
//		static constexpr int dim_element_value = mpl::at_c<Dimension, N>::type::value;
//		typedef typename mpl::at_c<Units, N>::type	unit;
//		static constexpr bool is_valid = (dim_element_value != 0 || (dim_element_value == 0 && unit::num == 1 && unit::den == 1)) && verify_units<Dimension, Units, N - 1>::is_valid;
//
//		static_assert(is_valid, "Dimensions whose elements are cero, must have corresponding unit to be 1:1!");
//	};
//
//	template<typename Dimension, typename Units>
//	struct verify_units<Dimension, Units, 0>
//	{
//		static constexpr int dim_element_value = mpl::at_c<Dimension, 0>::type::value;
//		typedef typename mpl::at_c<Units, 0>::type	unit;
//		static constexpr bool is_valid = (dim_element_value != 0 || (dim_element_value == 0 && unit::num == 1 && unit::den == 1));
//
//		static_assert(is_valid, "Dimensions whose elements are cero, must have corresponding unit to be 1:1!");
//	};
//
//	template<typename Dimension, typename Units>
//	struct verify_all_units
//	{
//		static constexpr bool is_valid = verify_units<Dimension, Units, mpl::size<Dimension>::value - 1>::is_valid;
//	};
//}

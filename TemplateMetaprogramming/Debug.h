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
	std::string formatRatio()
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

	void output(const std::string&  title, const std::string& str, const std::string& sep = " = ")
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

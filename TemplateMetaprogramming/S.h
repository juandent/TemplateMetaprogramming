#pragma once

#include <iostream>

namespace OverloadResolution
{

	class S
	{
	public:
		void f1()
		{
			std::cout << typeid(decltype(*this)).name() << std::endl;
		}
		void f2() &&
		{
			std::cout << typeid(decltype(*this)).name() << std::endl;
		}
		void f3() &
		{
			std::cout << typeid(decltype(*this)).name() << std::endl;
		}
	};


	inline void main()
	{
		S().f1();
		S().f2();
//		S().f3();
	}

}
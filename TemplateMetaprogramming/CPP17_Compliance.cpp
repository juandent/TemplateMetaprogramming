#include "stdafx.h"




namespace CPP17_Compliance
{
	std::pair<int, bool> getResult(int val)
	{
		auto ret = std::make_pair(10, true);
		return ret;
	}

	void testReducedScopes()
	{
		if (auto p(getResult(9)); p.second)
		{
			std::cout << p.first << std::endl;
		}
		else
		{
			p.first++;
		}

		switch (char c(getchar()); c)
		{
		case 'a': --c;
		default:
			++c;
		}
	}

	void bracketInitialization()
	{
		auto x = { 1 };
		auto y = { 1,2 };
	}

	void main()
	{
		auto[val, boolean] = getResult(8);

		testReducedScopes();

	}
}
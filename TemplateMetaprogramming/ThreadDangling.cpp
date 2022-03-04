#include "stdafx.h"



#include <thread>
#include <iostream>


void do_something(int& k)
{
	std::cout << "\nK: " << std::hex << k << std::endl;
}


struct func
{
	int& i;
	func(int& i_) : i{ i_ } {}
	void operator()()
	{
		for (auto j = 0u; j < 100'000'000u; ++j)
		{
			do_something(i);	// dangling reference!
		}
	}
};

void oops()
{
	int some_local_state = 0;
	func my_func{ some_local_state };
	std::thread mythread{ my_func };

	mythread.detach();
}


#include "stdafx.h"

struct Data
{
	std::string name;
	double value;
};

struct MoreData : Data
{
	bool done;
	inline static int val = 0;
	void print() const
	{
		
	}
};


template <typename T>
struct D : std::string, std::complex<T>
{
	std::string data;
};


void useD()
{
	D<float> s{ {"hello"},{4.5,6.7}, "world" };
	
}

void useAggregate()
{
	MoreData md{ {"juan", 21.00}, true};

	
}
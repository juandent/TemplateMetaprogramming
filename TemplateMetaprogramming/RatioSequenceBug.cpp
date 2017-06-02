
//#define TEST_BUG_BY_ITSELF 
#ifdef TEST_BUG_BY_ITSELF
#include <boost\mpl\at.hpp>
#include <ratio>


namespace mpl = boost::mpl;


template<typename RatioSequence, size_t N>
struct ratio_sequence_multiply
{
	friend ratio_sequence_multiply<RatioSequence, 0>;
	friend ratio_sequence_multiply<RatioSequence, N - 1>;


private:
	typedef typename mpl::at_c<RatioSequence, N>::type this_ratio;
	typedef typename ratio_sequence_multiply<RatioSequence, N - 1>::accumulative_ratio    prev_ratio;

public:
	typedef std::ratio_multiply<prev_ratio, this_ratio> accumulative_ratio;
};

template<typename RatioSequence>
struct ratio_sequence_multiply<RatioSequence, 0>
{ 
private:
	typedef typename mpl::at_c<RatioSequence, 0>::type this_ratio;
public:

	typedef this_ratio accumulative_ratio;
};

#else
#include "stdafx.h"
#include <iostream>

void testAssignmentOfIntToPointer()
{
	int ival, *pval;
	pval = { 0 };
	if (pval == nullptr)
	{
		ival = 1;
	}
}

void testConditionalOperator()
{
	int grade = 80;
	std::cout << ((grade < 60) ? "fail" : "pass") << std::endl;

	std::cout << (grade < 60) ? "fail" : "pass";

//	std::cout << grade < 60 ? "fail" : "pass";

}

#endif
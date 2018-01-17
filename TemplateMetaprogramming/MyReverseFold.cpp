#include "stdafx.h"

#include "MyReversedFold.h"

// sample sequence:
using MySeq = vector<long, float, short, double, float, long, long double>;


using r_xx = typename myReverseFold<MySeq, vector<>, push_back_external>::type;
using r_at00 = get_by_pos<2, r_xx>::type;

using r_xx_front = typename myReverseFold<MySeq, vector<>, push_front_external>::type;


// Good!!
void useReverseFold()
{
	r_xx anR;
	r_xx_front otherR;
}
#include "stdafx.h"

#include "MyFold.h"


// sample sequence:
using MySeq = vector<long, float, short, double, float, long, long double>;


using r_xx = typename myFold<MySeq, vector<>, push_back_external>::type;
using r_at00 = get_by_pos<2, r_xx>::type;

#ifdef TEST_PUSH_FRONT_EXTERNAL
using r_xx_front = typename myFold<MySeq, vector<>, push_front_external>::type;
using r_at00_front = get_by_pos<2, r_xx_front>::type;
#endif

// Good!!
void useMyFold()
{
	r_xx anR;
	r_at00 at2;
#ifdef TEST_PUSH_FRONT_EXTERNAL
	r_at00_front at2_front;
	r_xx_front otherR;
#endif
}

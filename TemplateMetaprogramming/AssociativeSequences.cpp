#include "stdafx.h"

///#include "exercise_3_1.hpp"
#include "AssociativeSequences.h"
#include <iostream>
#include <vector>
#include <boost/type_traits.hpp>
//#include <loki/Typelist.h>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/at.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/range_c.hpp>
#include <ratio>
#include <boost\mpl\vector.hpp>
#include <boost\mpl/size.hpp>
#include <boost\mpl\order.hpp>
#include <boost\mpl\map.hpp>
#include <boost\mpl\pair.hpp>
#include <boost\mpl\key_type.hpp>
#include <boost\mpl\value_type.hpp>
#include <boost\mpl\set.hpp>
#include <boost\mpl\pop_back.hpp>
#include <boost\mpl\pop_front.hpp>
#include <boost\mpl\erase.hpp>

#include "Debug.h"

// Dimensions (pg 40 -- C++ Template Metaprogramming
namespace mpl = boost::mpl;
using namespace mpl::placeholders;
using namespace std;

namespace AssociativeSequences {
	namespace Basics {
		void usingOrder()
		{
			typedef mpl::map< mpl::pair<int, unsigned>, mpl::pair<char, long>> m;
			auto p = mpl::order<m, int>::value;
			auto c = mpl::order<m, char>::value;
			typedef mpl::at<m, int>::type value_type_for_int_key;		// unsigned
			value_type_for_int_key v;
			typedef mpl::key_type< m, mpl::pair<int, unsigned>>::type key_type;
			key_type k;

			typedef mpl::erase<m, mpl::pair<char,long>>::type pbm;
			pbm pp;

			typedef mpl::key_type< mpl::set<>, mpl::pair<int, unsigned>>::type set_key_type;
			set_key_type sk;

			typedef mpl::value_type< mpl::set<>, mpl::pair<int, signed char>>::type set_value_type;
			set_value_type sv;

			typedef mpl::value_type< m, mpl::pair<int, signed char>>::type map_value_type;
			map_value_type mv;

			cout << "stop\n";
		}

	}
}

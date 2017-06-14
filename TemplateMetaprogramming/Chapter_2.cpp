#include "stdafx.h"

#include <boost/mpl/if.hpp>
#include <boost\mpl/eval_if.hpp>
#include <boost\mpl/identity.hpp>
#include <boost\mpl/apply.hpp>
#include <boost\mpl/next.hpp>
#include <boost\mpl/not_equal_to.hpp>
#include <boost\mpl/equal_to.hpp>
#include <boost\mpl/greater.hpp>
#include <boost\mpl/minus.hpp>
#include <boost\mpl/plus.hpp>
#include <boost\mpl/multiplies.hpp>
#include <boost\mpl/int.hpp>
#include <boost\mpl/placeholders.hpp>
#include <boost\mpl/assert.hpp>
#include <boost\mpl/is_sequence.hpp>
#include <boost\mpl/vector.hpp>
#include <boost\mpl/or.hpp>
#include <boost/type_traits.hpp>

namespace mpl = boost::mpl;

using namespace boost::mpl::placeholders;

namespace Section_2_5
{
	void aVoidFunction()
	{
		//...
	}

	void doPrimaryTypeCategorization(void* p)
	{
		constexpr decltype(p) ap = nullptr;
		constexpr bool _isvoid = boost::is_void<decltype(p)>::value;
		constexpr bool _isfunc = boost::is_function<decltype(aVoidFunction)>::value;

	}
}


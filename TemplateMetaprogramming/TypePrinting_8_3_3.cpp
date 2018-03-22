#include "stdafx.h"

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/print.hpp>
#include <boost\mpl/range_c.hpp>
#include <boost/mpl/placeholders.hpp>


namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

#if 0
#define static_warning_impl2(cond, msg, line) \
    struct static_warning_ ## line { \
        struct msg {}; \
        typedef typename boost::mpl::eval_if_c< \
            cond, \
            boost::mpl::identity<msg>, \
            boost::mpl::print<msg> \
        >::type msg ## _; \
    }

#define static_warning_impl1(cond, msg, line) \
    static_warning_impl2(cond, msg, line)

#define static_warning(cond, msg) \
    static_warning_impl1(cond, msg, __LINE__)



void warn()
{
	static_warning(sizeof(int) == 2, not2);
}
#endif


template<class T, class U>
struct plus_dbg
{
	typedef typename mpl::print< typename mpl::plus<T, U>::type > ::type type;
};

typedef mpl::fold<
	mpl::range_c<int, 1, 6>
	, mpl::int_<0>
	, plus_dbg<_1, _2>
>::type sum;


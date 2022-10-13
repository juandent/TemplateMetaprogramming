#include "stdafx.h"

namespace Loki
{
	template<bool> struct CompileTimeChecker
	{
		CompileTimeChecker(...) {}
	};

	template<> struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg) \
	{\
		class ERROR_##msg{};\
		sizeof(Loki::CompileTimeChecker<\
		(expr) == true>((ERROR_##msg())));\
	}


	class ERROR_DestinationTypeTooNarrow {};
	ERROR_DestinationTypeTooNarrow obj{};
	auto sss = sizeof(Loki::CompileTimeChecker<(sizeof(long) >= sizeof(long ))>(obj));




	struct DestinationTypeTooNarrow {};
	
	template<typename To, typename From>
	To safe_reinterpret_cast(From from)
	{
		STATIC_CHECK(sizeof(From) <= sizeof(To), DestinationTypeTooNarrow);
		return static_cast<To>(from);
		//return reinterpret_cast<To>(from);
	}

	void useSafeCast()
	{
		long pointer = 15;
		auto c = safe_reinterpret_cast<int>(pointer);
	}
}
#pragma once

#include <type_traits>

namespace sqlpp
{
	struct consistent_t : std::true_type
	{
		static void _() {};
	};
}  // namespace sqlpp


namespace sqlpp
{

	struct MockDB
	{
		MockDB() = default;

		// Directly executed statements start here
		template <typename T>
		auto _run(const T& t, ::sqlpp::consistent_t) -> decltype(t._run(*this))
		{
			return t._run(*this);
		}


		template <typename T>
		auto _run(const T& t) //-> decltype(t._run(*this))
		{
			return t._run(*this);
		}

		template <typename Check, typename T>
		auto _run(const T& t, Check)->Check;
	};
}


struct Runnable
{
	int _run(const sqlpp::MockDB& p) const
	{
		return 0;
	}
};


void doit()
{
	using namespace sqlpp;

	Runnable rnable;
	MockDB mdb{};

	using t = decltype(rnable._run(mdb));
	t* pT;

	auto x = mdb._run(rnable, consistent_t{});

	//auto y = mdb._run(1);

}
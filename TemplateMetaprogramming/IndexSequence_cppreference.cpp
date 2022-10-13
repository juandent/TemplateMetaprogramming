
#include <tuple>
#include <iostream>
#include <utility>
#include <array>
#include <vector>
 

namespace seq
{

	using namespace std;

	template<typename T, T... ints>
	void print_sequence(std::integer_sequence<T, ints...> int_seq)
	{
		cout << "The sequence of size " << int_seq.size() << ": ";
		((cout << ints << ' '), ...);
		cout << endl;
	}


	// convert array into a tuple
	template<typename Array, std::size_t ...I>
	auto a2t_impl(const Array& a, std::index_sequence<I...> s)
	{
		return make_tuple(a[I]...);
	}

	template<typename T, size_t N, typename Indices = make_index_sequence<N>>
	auto a2t(const array<T, N>& a)
	{
		return a2t_impl(a, Indices{});
	}

	// pretty  print a tuple
	template<typename Ch, typename Tr, typename Tuple, size_t...Is>
	void print_tuple_impl(basic_ostream<Ch, Tr>& os, const Tuple& t, index_sequence<Is...>)
	{
		((os << (Is == 0 ? "" : ", ") << get<Is>(move(t))), ...);
	}

	template<typename Ch, typename Tr, typename...Args>
	auto& operator<<(basic_ostream<Ch, Tr>& os, const tuple<Args...>& t)
	{
		print_tuple_impl(os, t, index_sequence_for<Args...>{});
		return os;
	}

	void useSequenceCPP()
	{
		print_sequence(integer_sequence<unsigned, 9, 2, 4, 8, 6, 1>{});

		array<int, 4> ar{ 5,2,8,6 };

		auto tup = a2t_impl(ar, make_index_sequence<4>{});

		auto up = a2t_impl(ar, index_sequence<3, 1, 2, 0>{});

		vector<int> v{ 12,15,67,8,90 };

		auto tu = a2t_impl(v, make_index_sequence<5>{});

		cout << a2t(ar);

	}

}

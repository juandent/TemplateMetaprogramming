#include <algorithm>
#include <array>
#include <iterator>
#include <ranges>


template<typename T>
class Array
{
public:
	consteval Array(T* array, int size) noexcept : _array(array), _size(size) {}

	~Array() noexcept  { delete[] _array; }

	T& operator[](int index) { return _array[index]; }
	int size() const noexcept { return _size; }

	friend void swap(Array& left, Array& right)  noexcept
	{
		using std::swap;
		swap(left.array_, right._array);
		swap(left._size, right._size);
	}

	Array& operator=(Array other) noexcept
	{
		swap(*this, other);
		return *this;
	}
	constexpr Array( const Array& other) : _array(new T[other._size]), _size(other._size)
	{
		std::copy_n(other._array, _size, _array);
	}

	Array(Array&& other) noexcept :   _array(std::exchange(other._array, nullptr)), _size(std::exchange(other._size, 0))
	{}
private:
	T* _array;
	int _size;
};



namespace detail
{
	struct contains_fn final
	{
		template<std::input_iterator It,
			std::sentinel_for<It> Sent,
			typename T,
			typename Proj=std::identity>

		requires std::indirect_binary_predicate<std::ranges::equal_to,
				std::projected<It, Proj>,
				const T*>

		constexpr bool operator()(It first, Sent last, const T& value, Proj projection = {}) const
		{
			while (first != last && std::invoke(projection, *first) != value)
				++first;
			return first != last;
		}

		template<std::ranges::input_range Range, typename T, typename Proj = std::identity>
			requires std::indirect_binary_predicate<std::ranges::equal_to,
		std::projected<std::ranges::iterator_t<Range>, Proj>, const T*>

		constexpr bool operator()(Range&& range, const T& value, Proj projection = {})
		{
			return (*this)(std::ranges::begin(range), std::ranges::end(range), value, std::move(projection));
		}

	};
	inline contains_fn contains{};

	int use()
	{
		auto ints = std::ranges::views::iota(0) | std::ranges::views::take(5);
		return contains(ints, 42);
	}

}
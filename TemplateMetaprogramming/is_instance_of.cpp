
#include <set>
#include <type_traits>
#include <vector>

/*
template <class _Kty, class _Pr = std::less<_Kty>, class _Alloc = std::allocator<_Kty>>
class set;

template <bool _Val>
using bool_constant = std::integral_constant<bool, _Val>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;
*/

template <template <typename...> class, typename T>
struct is_instance_of : std::false_type {};

template <template <typename...> class Tm, typename ... Ts>
struct is_instance_of<Tm, Tm<Ts...>> : std::true_type {};

template <typename T>
constexpr bool is_instance_of_set = is_instance_of<std::set, T>::value;

static_assert(is_instance_of_set<std::set<int>>);
static_assert(!is_instance_of_set<std::vector<int>>);

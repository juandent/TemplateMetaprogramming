
#include <mutex>
#include <concepts>
#include <array>
#include <vector>

std::mutex globalOsMutex{};


template<typename T>
void DoLocked(T&& f) requires std::invocable<T>
{
	std::lock_guard lck(globalOsMutex);

	f();
}

void DoLocked(std::invocable auto&& f)
{
	std::lock_guard lck(globalOsMutex);
	f();
}

constexpr  auto GetSize(const auto& t ={})
{
	return t.size();
}

template<typename T, size_t N>
concept SizeCheck = (GetSize<T>() == N);


template<typename T, size_t N>
concept SizeCheck2 = requires { GetSize<T>() == N; };

template<typename T, size_t N>
concept SizeCheck3 = requires (T t)  { requires t.size() == N; };



void SendOnePing(const SizeCheck3<1> auto& cont) {}

namespace _1_9
{
	void use()
	{
		constexpr std::array<int, 1> a{5566};
		SendOnePing(a);
		constexpr auto s = GetSize(a);

		std::vector<int> b{ 2 };
		// SendOnePing(b);
		auto ss = GetSize(b);
	}
}


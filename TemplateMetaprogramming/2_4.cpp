#include <string>
#include <array>
#include <iostream>
#include <coroutine>
#include <optional>
#include <cassert>
#include <functional>
#include <vector>

using byte = unsigned char;

static constexpr byte ESC{ 'H' };
static constexpr byte SOF{ 0x10 };

template<typename T>
void ProcessNextByte(byte b, T& frameCompleted)
{
	static std::string frame{};
	static bool	inHeader{ false };
	static bool wasESC{ false };
	static bool lookingForSOF{ false };

	if(inHeader)
	{
		if( (ESC == b) && not wasESC)
		{
			wasESC = true;
			return;
		}
		else if(wasESC)
		{
			wasESC = false;

			if((SOF == b) || (ESC != b))
			{
				if (SOF == b) { frameCompleted = frame; }

				frame.clear();
				inHeader = false;
				return;
			}
		}
		frame += static_cast<char>(b);
	}
	else if(( ESC==b) && !lookingForSOF)
	{
		lookingForSOF = true;
	}
	else if( (SOF == b) && lookingForSOF)
	{
		inHeader = true;
		lookingForSOF = false;
	}
	else
	{
		lookingForSOF = false;
	}
}


void printAscii()
{
	std::array<char, 6> arr{ 0x9, 'a', 'b', 0x9, 'c', 'd' };

	for (char c : arr)
	{
		std::cout << c;
	}
	std::cout << "\n";
}

void parseHelloWorld()
{
	std::array<char, 22> arr{ 0x70, ESC, SOF, ESC, 'H', 'e', 'l','l','o', ESC,SOF, 0x9,ESC,SOF, 'W','o','r','l','d', ESC, SOF };
	std::string frame;
	for (int i = 0; i < 22; ++i)
	{
		char b = arr[i];
		ProcessNextByte(b, frame);
		std::cout << arr[i] << ":" << frame << std::flush;
	}
	std::cout << "\n";
}



template<typename T, typename G, typename...Bases>
struct promise_type_base : public Bases...
{
	T mValue;

	auto yield_value(T value)
	{
		mValue = value;
		return std::suspend_always{};
	}
	G get_return_object() { return G{ this }; }

	std::suspend_always initial_suspend() { return {}; }
	std::suspend_always final_suspend()  noexcept { return {}; }
	void	return_void() {}
	void	unhandled_exception() { std::terminate(); }
};

template<typename T>
struct awaitable_promise_type_base
{
	std::optional<T> mRecentSignal;

	struct awaiter
	{
		std::optional<T>& mRecentSignal;

		bool await_ready() { return mRecentSignal.has_value(); }
		void await_suspend(std::coroutine_handle<>) {}

		T await_resume()
		{
			assert(mRecentSignal.has_value());

			auto tmp = *mRecentSignal;
			mRecentSignal.reset();
			return tmp;
		}
	};

	[[nodiscard]] awaiter await_transform(T)
	{
		return awaiter{ mRecentSignal };
	}
};



template<typename T, typename U>
struct [[nodiscard]] async_generator
{
	using promise_type = promise_type_base<T, async_generator, awaitable_promise_type_base<U>>;

	using PromiseTypeHandle = std::coroutine_handle<promise_type>;

	T operator()()
	{
		auto tmp{ std::move(mCoroHdl.promise().mValue) };
		mCoroHdl.promise().mValue.clear();
		return tmp;
	}

	void SendSignal(U signal)
	{
		mCoroHdl.promise().mRecentSignal = signal;
		if (not mCoroHdl.done()) { mCoroHdl.resume(); }
	}

	async_generator(const async_generator&) = delete;
	async_generator(async_generator&& rhs)
		: mCoroHdl(std::exchange(rhs.mCoroHdl, nullptr))
	{}

	~async_generator()
	{
		if (mCoroHdl) { mCoroHdl.destroy(); }
	}
private:
	friend promise_type;

	explicit async_generator(promise_type* p)
		: mCoroHdl(PromiseTypeHandle::from_promise(*p))
	{}

	PromiseTypeHandle mCoroHdl;
};


using FSM = async_generator<std::string, byte>;

FSM Parse()
{
	while (true)
	{
		byte b = co_await byte{};
		if (b != ESC) { continue; }

		b = co_await byte{};

		std::string frame{ };
		while (true)
		{
			b = co_await byte{};

			if (ESC == b)
			{
				b = co_await byte{};

				if (SOF == b)
				{
					co_yield frame;
					break;
				}
				else if (ESC != b)
				{
					break;
				}
			}
			frame += b;
		}
	}
}


void useParse()
{
	FSM ret = Parse();
	std::array<char, 22> arr{ 0x70, ESC, SOF, ESC, 'H', 'e', 'l','l','o', ESC,SOF, 0x9,ESC,SOF, 'W','o','r','l','d', ESC, SOF };
	std::vector<std::string> words;
	for (int i = 0; i < 22; ++i)
	{
		char b = arr[i];
		ret.SendSignal(b);
		auto s = ret();
		if(! s.empty())
		{
			words.push_back(s);
		}
		std::ignore = s;
	}
	auto s = ret();

	for(const auto& w : words)
	{
		std::cout << w << std::endl;
	}
}


namespace coro_iterator
{
	template<typename PT>
	struct iterator
	{
		std::coroutine_handle<PT> mCoroHndl{ nullptr };

		void resume()
		{
			if (not mCoroHndl.done()) { mCoroHndl.resume(); }
		}
		iterator() = default;
		iterator(std::coroutine_handle<PT> hco)
			: mCoroHndl(hco)
		{
			resume();
		}

		void operator++() { resume(); }
		bool operator==(const iterator&) const
		{
			return mCoroHndl.done();
		}
		const auto& operator*() const
		{
			return mCoroHndl.promise().mValue;
		}
	};
}


template<typename T>
struct generator
{
	using promise_type = promise_type_base<T, generator>;
	using PromiseTypeHandle = std::coroutine_handle<promise_type>;


	using iterator = coro_iterator::iterator<promise_type>;
	iterator begin() { return mCoroHdl; }
	iterator end() { return {}; }

	generator(const generator&) = delete;
	generator(generator&& rhs)
		: mCoroHdl(std::exchange(rhs.mCoroHdl, nullptr))
	{}

	~generator()
	{
		if (mCoroHdl) { mCoroHdl.destroy(); }
	}

private:
	friend promise_type;

	explicit generator(promise_type*p)
		: mCoroHdl(PromiseTypeHandle::from_promise(*p))
	{}

	PromiseTypeHandle mCoroHdl;
};

generator<byte> sender(std::vector<byte> fakeBytes)
{
	for (const auto& b : fakeBytes) { co_yield b; }
}

void HandleFrame(std::string frame)
{
	std::cout << frame << std::endl;
}


void ProcessStream(generator<byte>& stream, FSM& parse, std::function<void(std::string)> f)
{
	for(const auto& b : stream)
	{
		parse.SendSignal(b);

		if(const auto& res = parse(); res.length())
		{
			f(res);
		}
	}
}


void useFakeBytes()
{

	std::vector<byte> fakeBytes1{ 0x70, ESC, SOF, ESC, 'H', 'e', 'l','l','o', ESC,SOF, 0x9,ESC,SOF, 'W','o','r','l','d', ESC, SOF };
	auto stream1 = sender(std::move(fakeBytes1));

	auto p = Parse();

	ProcessStream(stream1, p, HandleFrame);

}

namespace alternative_impl
{

	template<typename T, typename G, bool InitialSuspend>
	struct promise_type_base
	{
		T mValue;

		std::suspend_always yield_value(T value)
		{
			mValue = value;
			return {};
		}

		auto initial_suspend()
		{
			if constexpr (InitialSuspend)
			{
				return std::suspend_always{};
			}
			else
			{
				return std::suspend_never{};
			}
		}

		std::suspend_always final_suspend() noexcept { return {}; }
		G get_return_object() { return G(this); }

		void unhandled_exception() { std::terminate(); }
		void return_void() {}
	};

	template<typename T, bool InitialSuspend= true>
	struct generator
	{
		using promise_type = promise_type_base<T, generator, InitialSuspend>;
		using PromiseTypeHandle = std::coroutine_handle<promise_type>;

		using iterator = coro_iterator::iterator<promise_type>;

		iterator begin() { return mCoroHdl; }
		iterator end() { return {}; }

		generator(generator const&) = delete;
		generator(generator&& rhs) : mCoroHdl(std::exchange(rhs.mCoroHdl, nullptr)) {}

		~generator()
		{
			if (mCoroHdl) { mCoroHdl.destroy(); }
		}

		T operator()()
		{
			T tmp{};
			std::swap(tmp, mCoroHdl.promise().mValue);
			return tmp;
		}

	private:
		friend promise_type;
		explicit generator(promise_type* p) : mCoroHdl(PromiseTypeHandle::from_promise(*p)) {}

	protected:
		PromiseTypeHandle mCoroHdl;
	};

	class DataStreamReader	// awaitable
	{
	public:
		DataStreamReader() = default;

		DataStreamReader& operator=(DataStreamReader&&) noexcept = delete;

		struct Awaiter
		{
			Awaiter& operator=(Awaiter&&) noexcept = delete;
			Awaiter( DataStreamReader& event) noexcept : mEvent(event)
			{
				mEvent.mAwaiter = this;
			}

			bool await_ready() const noexcept
			{
				return mEvent.mData.has_value();
			}

			void await_suspend(std::coroutine_handle<> coroHdl) noexcept
			{
				mCoroHdl = coroHdl;
			}

			byte await_resume() noexcept
			{
				assert(mEvent.mData.has_value());
				return *std::exchange(mEvent.mData, std::nullopt);
			}
			void resume() { mCoroHdl.resume(); }

		private:
			DataStreamReader& mEvent;
			std::coroutine_handle<> mCoroHdl{};
		};

		auto operator co_await() noexcept { return Awaiter{ *this }; }

		void set(byte b)
		{
			mData.emplace(b);
			if (mAwaiter)	mAwaiter->resume();
		}

	private:
		friend struct Awaiter;
		Awaiter* mAwaiter{};
		std::optional<byte> mData{};
	};

	using FSM = generator<std::string, false>;

	FSM Parse(DataStreamReader& stream)
	{
		while (true)
		{
			byte b = co_await stream;
			if (b != ESC) { continue; }

			b = co_await stream;

			std::string frame{ };
			while (true)
			{
				b = co_await stream;

				if (ESC == b)
				{
					b = co_await stream;

					if (SOF == b)
					{
						co_yield frame;
						break;
					}
					else if (ESC != b)
					{
						break;
					}
				}
				frame += b;
			}
		}
	}

	void useFakeBytes()
	{

		std::vector<byte> fakeBytes1{ 0x70, ESC, SOF, ESC, 'H', 'e', 'l','l','o', ESC,SOF, 0x9,ESC,SOF, 'W','o','r','l','d', ESC, SOF };
		auto stream1 = sender(std::move(fakeBytes1));

		DataStreamReader dr{};
		
		auto p = Parse(dr);

		for(const auto& b : stream1)
		{
			dr.set(b);	// send new byte to waiting DataStreamReader

			if (const auto& res = p(); res.length()) { HandleFrame(res); }

		}

		std::vector<byte> fakeBytes2{ 0x70, ESC, SOF, ESC, 'H', 'i', ESC,SOF, 0x9,ESC,SOF, 'W','o','r','l','d', ESC, SOF };
		auto stream2 = sender(std::move(fakeBytes2));

		for (const auto& b : stream2)
		{
			dr.set(b);	// send new byte to waiting DataStreamReader

			if (const auto& res = p(); res.length()) { HandleFrame(res); }

		}


		// ProcessStream(stream1, p, HandleFrame);

	}

}
#include "stdafx.h"

struct pixel_map{};

class screensaver
{
public:
	struct customization
	{
		virtual ~customization(){}
		virtual float operator()(float) const = 0;
	};

	[[nodiscard]] explicit screensaver(std::unique_ptr<customization> get_seed)
		: get_seed(std::move(get_seed))
	{
	}
	pixel_map next_screen()
	{
		float center_pixel_brightness = 50.44f;
		float seed = (*this->get_seed)(center_pixel_brightness);

		//
		return {};
	}

private:
	std::unique_ptr<customization> get_seed;
};

using floatfunc = float(*)(float);

// manual type erasure
struct hypnotic : screensaver::customization
{
	[[nodiscard]] explicit hypnotic( std::initializer_list<int> list)
		: state{ list}
	{}

	float operator()(float arg) const override
	{
		auto x0 = this->state[0];
		return (x0 * 4.67f);
	}
	std::vector<int> state;
};

struct funwrapper : screensaver::customization
{
	[[nodiscard]] explicit funwrapper(floatfunc f)
		: f(f)
	{
	}

	float operator()(float arg) const override
	{
		return this->f(arg);
	}

	floatfunc f;
};

// automatic type erasure
class screensaver2
{
private:
	struct customization
	{
		virtual ~customization() {}
		virtual float operator()(float arg) const = 0;
	};
	template<typename F>
	struct wrapper : customization
	{
		[[nodiscard]] explicit wrapper(F f)
			: f(f)
		{
		}

		float operator()(float arg) const override
		{
			return this->f(arg);
		}
	private:
		F f;
	};
public:
	template<typename F>
	[[nodiscard]] explicit screensaver2(F const& f)
		: get_seed(new wrapper<F>{f})
	{
	}

	pixel_map next_screen()
	{
		float center_pixel_brightness = 50.44f;
		float seed = (*this->get_seed)(center_pixel_brightness);

		//
		return {};
	}
private:
	std::unique_ptr<customization> get_seed;
};

float f(float arg)
{
	return arg * 1.5f;
}

struct F
{
	float operator()(float arg) const
	{
		return arg * 2.0f;
	}
};

class float_function
{
private:
	// interface
	struct impl
	{
		virtual ~impl() {}
		virtual impl* clone() const = 0;
		virtual float operator()(float arg) const = 0;
	};

	template<typename F>
	struct wrapper : impl
	{
		[[nodiscard]] explicit wrapper(const F& f)
			: f(f)
		{
		}

		impl* clone() const override
		{
			return new wrapper(this->f);
		}
		float operator()(float arg) const override
		{
			return f(arg);
		}
	private:
		F f;
	};
public:
	// implicit conversion from F
	template<typename F>
	float_function( F const& f)
		: pimpl(new wrapper<F>(f))
	{}

	float_function(const float_function& rhs)
		: pimpl(rhs.pimpl->clone())
	{
	}

	float_function& operator=(const float_function& other)
	{
		if (this == &other)
			return *this;
		pimpl.reset(other.pimpl->clone());
		return *this;
	}

	float operator()(float x) const
	{
		return (*this->pimpl)(x);
	}

private:
	std::unique_ptr<impl> pimpl;
};

class screensaver3
{
public:
	explicit screensaver3(const float_function& f)
		: get_seed(f)
	{}

	pixel_map next_screen()
	{
		float center_pixel_brightness = 5.55f;
		float seed = this->get_seed(center_pixel_brightness);
		return {};
	}
private:
	float_function get_seed;
};

void callScreensaver()
{
	screensaver scr{ std::unique_ptr<screensaver::customization>(new hypnotic{1,2,3}) };

	F ff;
	screensaver2 scr2{ ff };
	scr2.next_screen();

	screensaver3 scr3{ ff };
	scr3.next_screen();
}


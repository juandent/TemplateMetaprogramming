#include "stdafx.h"

#include <iterator>

template<typename T>
struct ordered
{
	bool operator>(T const& rhs) const
	{
		// locate full derived object
		T const& self = static_cast<T const&>(*this);
		return rhs < self;
	}
};


class Int : public ordered<Int>
{
public:
	[[nodiscard]] explicit Int(int value)
		: value(value)
	{
	}
	bool operator<(Int const& rhs) const
	{
		return this->value < rhs.value;
	}

	int value;
};

// should crash!!

class bogus : public ordered<Int>
{
public:
	bogus(int val) : value(val) {}

private:
	int value;
};

void useInt()
{
	bool ok = Int(4) < Int(6);
	ok = Int(9) > Int(6);

	ok = bogus(2) > Int(5);	// should crash!
}


namespace crtp
{
	template<typename T>
	struct signed_number
	{
		constexpr friend T abs(T x)
		{
			return x < 0 ? -x : x;
		}
	};
}

class Float : public crtp::signed_number<Float>
{
	float value;
public:
	constexpr [[nodiscard]] Float(float value)
		: value(value)
	{
	}
	Float operator-() const
	{
		return -value;
	}
	bool operator<(float x) const
	{
		return value < x;
	}
};

constexpr Float minus_pi{ -3.14159265f };
Float pi{ abs(minus_pi) };


void useCrtp()
{
	Float pi{ abs(Float{-3.14f}) };
}
// Example of Argument Dependent Lookup ADL:

namespace utility
{
	// fill the range with zeroes
	template<typename Iterator>
	Iterator clear(Iterator const& start, Iterator const& finish)
	{
		std::transform(start, finish, start, [](auto& elem)
			{
				return 0;
			});
		return start;
	}

	// perform some transformation on the sequence
	template<typename Iterator>
	int munge(Iterator start, Iterator finish)
	{
		// start =					// error! cannot assign void
			clear(start, finish);	// calls Paint::clear because of ADL
		return 0;	// dummy code
	}

}

namespace Paint
{
	template<typename Canvas, typename Color>
	void clear(Canvas& c, const Color& col)
	{
		// return 0;
	}


	struct some_canvas
	{
		some_canvas& operator=(int t) { return *this; }	// to  silence the compiler when Paint::clear is not compiled
	};
	struct black {};

	void useUtility()
	{
		std::list<some_canvas> canvases(10);
		int x = utility::munge(canvases.begin(), canvases.end());
		std::vector<int> vec {1,2,3,4};
		utility::clear(vec.begin(), vec.end());
	}
}

template<typename Derived>
struct vehicle
{
	int model;
};

template<typename Derived>
struct screw
{
	double diameter;
};

class AVehicle : public vehicle<AVehicle>
{
public:
};

class AScrew : public screw<AScrew>
{
public:
};

template<typename Vehicle>
void drive(vehicle<Vehicle> const& v)
{
	Vehicle const& t = static_cast<Vehicle const&>(v);
	///....
}

template<typename Screw>
void drive(screw<Screw> const& v)
{
	Screw const& s = static_cast<Screw const&>(v);
	///....
}

void useDrive()
{
	drive(AVehicle{2020});
	drive(AScrew{ 5.55 });

	AVehicle vv{ 2022 };
	drive(vv);

}


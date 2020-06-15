#pragma once

#include <cmath>


struct Point
{
	double x, y;
};

template<typename T>
T sqr(T x)
{
	static_assert(std::is_arithmetic_v<T>);
	return x * x;
}

inline double operator -(const Point& a, const Point& b )
{
	return std::sqrt( sqr(a.x - b.x) + sqr(a.y - b.y));
}

struct Shape
{
	virtual double area() = 0;
	virtual ~Shape() {}
};



struct Triangle : Shape
{
	Point a, b, c;
	// these are wrong!
	double get_height() const { return a - b; }
	double get_width() const { return a - c; }
	
	double area() override
	{
		return get_height() * get_width() / 2;
	}
};


struct Rectangle : Shape
{
	Point left_upper;
	Point right_lower;

	double get_height() const { return 10; }
	double get_width() const { return 20; }
	
	double area() override
	{
		return get_height() * get_width();
	}
};



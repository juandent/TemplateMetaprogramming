#include "stdafx.h"

template<typename GeoObj>
void myDraw(const GeoObj& obj)
{
	obj.draw();
}


class Triangle
{
public:
	void draw() const
	{
		// ..... draw a triangle
	}
};

class Square
{
public:
	unsigned draw(int x=0, int y=0) const
	{
		// ..... draw a square
		return 0;
	}
};

void useStaticPolymorphism()
{
	Triangle t;
	Square s;

	myDraw(t);
	myDraw(s);
}


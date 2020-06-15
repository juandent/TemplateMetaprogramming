#include "stdafx.h"

template<int v>
struct Int2Type
{
	enum { value = v };
};

template<typename Elem, bool isPolimorphic>
class NiftyContainer
{
private:
	void DoSomething( Elem* obj, Int2Type<true> )
	{
		Elem* newObj = obj->Clone();
		// polymorphic algorithm
	}
	void DoSomething(Elem* obj, Int2Type<false>)
	{
		Elem* newObj = new Elem(*obj);
		// non-polymorphic algorithm
	}
public:
	void DoSomething( Elem* obj)
	{
		DoSomething(obj, Int2Type<isPolimorphic>());
	}
};

struct Person
{
	std::string name;
	Person(const Person& pers) = default;
};

struct Point
{
	int x;
	int y;
	Point() = default;
	Point(int x, int y) : x{x}, y{y} {}
};

struct Shape
{
	[[nodiscard]] virtual Shape* Clone() = 0;
	virtual ~Shape() {}
};

struct Triangle : Shape
{
	Point p1{};
	Point p2{};
	Point p3{};
	Triangle() = default;
	Triangle(Point p1, Point p2, Point p3) : p1{p1}, p2{p2}, p3{p3} {}
	
	 virtual Shape* Clone() override
	{
		return new Triangle{ p1,p2,p3 };
	}
};

void useNifty()
{

	[[maybe_unused]]
	NiftyContainer<Triangle, true> polyContainer;
	[[maybe_unused]]
	NiftyContainer < Person, false> nonPoly_Container;

	Triangle tri{ {1,2}, {3,4}, {5,6} };
	Triangle triangle;
	int a;
	std::string str;
}


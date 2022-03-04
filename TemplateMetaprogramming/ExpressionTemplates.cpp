#include "stdafx.h"


#if 0
struct plus;
struct minus;

using namespace std::literals;



// expression tree node
template<class L, class OpTag, class R>
struct Expression
{
	Expression(L l, R r) : l{l}, r{r} {}
	~Expression()
	{
		int i = 0;
		std::cout << "~Expression this = " << std::hex << this << std::endl;
	}

	auto operator[](unsigned index) const
	{
		return OpTag::apply(l[index], r[index]);
	}

	L const& l;
	R const& r;
};


// addition operator
template<class L, class R>
Expression<L, plus, R> operator+(L const& l, R const& r)
{
	return Expression<L, plus, R>(l, r);
}


template<unsigned Cols>
struct Vector;

template<size_t Cols>
void display(Vector<Cols>& r, std::string);

template<unsigned Rows, unsigned Cols>
struct Array;

template<size_t Rows, size_t Cols>
void display(Array<Rows, Cols>& r, std::string);




template<unsigned Cols>
struct Vector
{
	Vector() = default;
	Vector(const Vector& rhs)
	{
		for(int i =0; i < Cols; ++i)
		{
			data[i] = rhs[i];
		}
		display(*this, "Vector(const Vector& rhs)");
	}
	Vector(std::initializer_list<float> list)
	{
		auto p = std::begin(list);

		for(int i=0; i < Cols; ++i, ++p)
		{
			data[i] = *p;
		}
		display(*this, "Vector(std::initializer_list<float> list)");
	}
	~Vector()
	{
		display(*this, "~Vector");
		int i = 0;
	}


	float data[Cols];

	float operator[](size_t index) const
	{
		return data[index];
	}

	float& operator[](size_t index)
	{
		return data[index];
	}

	Vector<Cols>& operator=(const Vector<Cols>& rhs)
	{
		for (int i = 0; i < Cols; ++i)
		{
			data[i] = rhs[i];
		}
		return *this;
	}
};

template<size_t N>
Vector<N> operator+(const Vector<N>& lhs, const Vector<N>& rhs)
{
	Vector<N> res;
	for(int i=0; i < N; ++i)
	{
		res[i] = lhs[i] + rhs[i];
	}
	return res;
}



template<unsigned Rows, unsigned Cols>
struct Array
{
	Vector<Cols> data[Rows];

	Array() {}
	Array(const std::initializer_list<Vector<Cols>>& list)
	{
		auto p = std::begin(list);
		for(int i=0; i < Rows; ++i, ++p)
		{
			data[i] = *p;
		}
		display(*this, "Array(const std::initializer_list<Vector<Cols>>& list)");
	}
	~Array()
	{
		display(*this, "~Array");
	}
	Array(const Array& rhs)
	{
		for(int i=0; i < Rows; ++i)
		{
			data[i] = rhs[i];
		}
	}

	template<typename Expr>
	Array& operator=(Expr const& x)
	{
		for( unsigned i=0; i < Rows; ++i)
		{
			(*this)[i] = x[i];
			// data[i] = tmp;
		}
		return *this;
	}

	const Vector<Cols>& operator[](size_t index) const
	{
		return data[index];
	}
	Vector<Cols>& operator[](size_t index)
	{
		return data[index];
	}

};


struct plus
{
	template<size_t N>
	static auto apply(Vector<N> a, Vector<N> b)
	{
		return a + b;
	}
};

struct minus
{
	template<typename Elem>
	static auto apply(Elem a, Elem b)
	{
		return a - b;
	}
};


template<size_t Cols>
void display(Vector<Cols>& r, std::string title)
{
	std::cout << title << " Vector<Cols> at " << std::hex << &r << "\n";
	for (int j = 0; j < Cols; ++j)
		std::cout << r[j] << " ";

	std::cout << std::endl;
}



template<size_t Rows, size_t Cols>
void display(Array<Rows, Cols>& r, std::string title)
{
	std::cout << title << " Array<Row, Cols> at " << std::hex << &r << "\n";
	for (int i = 0; i < Rows; ++i)
	{
		display(r[i], "display(Array)& ["s + std::to_string(i) + "]\n\n");
		for (int j = 0; j < Cols; ++j)
		{
			std::cout << r[i][j] << " ";
		}
		std::cout << std::endl;
	}
	// std::cout << std::endl;
}


void useExpr()
{
	// Vector<2> v{ 1.3,2.3 };
	Array<2, 2> x;

	Vector<2> a0{ 1,2 };
	Vector<2> a1{ 3,4 };
	Array<2, 2> a{ a0, a1 };
	display(a.data[0], "useExpr");
	display(a.data[1], "useExpr");

	//Array<2, 2> a{ {1,2}, {3, 4} };

	Vector<2> b0{ 2,5 };
	Vector<2> b1{ 5,8 };
	Array<2, 2 > b{ b0, b1 };

	Vector<2> c0{ 3,6 };
	Vector<2> c1{ 7,9};
	Array<2,2> c{ c0,c1 };

	display(a, "useExpr()");
	display(b, "useExpr()");

//	auto y = a[0];

	x = a + b;
	display(x, "useExpr()");


	// Array<2, 2> y = ;
	x = a + b + c;

	display(x, "useExpr()");

	x = a + b + c;
	display(x, "useExpr()");

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			std::cout << x[i][j];

}
#endif

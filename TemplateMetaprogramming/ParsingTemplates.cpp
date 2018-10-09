#include "stdafx.h"

// dependent names in using declarations

template<typename T>
class BXT
{
	public:
		using Mystery = T;
		template<typename U>
		struct Magic
		{
			int n = 0;
			//typename U::X * px;
		};
};

template<typename T>
class DXTT : private BXT<T>
{
public:
	using typename BXT<T>::Mystery;
	Mystery* p;
};

template<typename T>
class DXTM : private BXT<T>
{
public:
	using typename BXT<T>::template Magic;
	Magic<T>* plink;
};

namespace withC11_workaround
{
	template<typename T>
	class DXTM : private BXT<T>
	{
	public:
		// use alias template
		template<typename U>
		using Magic = typename BXT<T>::template Magic<T>;
		Magic<T>* plink;
	};
}
void useDXTM()
{
	BXT<int>::Magic<int> magic_int;

	DXTM<int> a{};
	a.plink = &magic_int;
	a.plink->n = 33;

	withC11_workaround::DXTM<int> b{};
	b.plink->n = 55;

}


namespace N
{
	class X
	{

	};

	template<int I> void select(X*)
	{}
}

template<typename T> void select();	// marks select as a function template

void g(N::X* xp)
{
	select<3>(xp);
}


void f() {}

template<int x> void nondependentCall()
{
	f(x);
}

template<int N> void instantiationDependentBound()
{
	constexpr int x = sizeof(N);
	constexpr int y = sizeof(N) + 1;
//	int array[x - y];	// negative subscript!
}

void useF()
{
	//nondependentCall<4>();
	instantiationDependentBound<5>();
}


namespace InheritanceAndClassTemplates
{
	template<typename X>
	class Base
	{
	public:
		int basefield;
		using T = int;
	};

	// non dependent base class=> complete type that can be determined without knowing the template arguments
	template<typename T>
	class D2 : public Base<double>
	{
	public:
		void f() { basefield = 3; }
		T strange;					// means Base<double>::T (==> int)
	};

	// dependent base class	(pg 237  C++ Templates: The Complete Guide, 2nd edition
	template<typename T>
	class DD : public Base<T>
	{
	public:
		void f() { this->basefield = 0; }		// #1 problem
	};
	
	template<>
	class Base<bool>
	{
	public:
		enum { basefield = 42 };		// #2 tricky
	};

	//template class DD<bool>;

	void g(DD<bool>& d)
	{
		//d.f();							// #3 oops
	}
}

namespace Instantiation
{
	namespace POI
	{
		class MyInt
		{
			int m_i;
		public:
			MyInt(int i)
				: m_i{i}
			{}
			int get() const { return m_i; }
		};

		MyInt operator-(MyInt const& a)
		{
			return MyInt(-a.get());
		}

		bool operator > (MyInt const& l, MyInt const& r)
		{
			return l.get() > r.get();
		}

		using Int = MyInt;

		template<typename T>
		void ff(T i)
		{
			if (i > 0)
			{
				gg(-i);
			}
		}

		void hh(Int x)
		{
			ff<Int>(x);
		}
		
		void gg(Int x)
		{
			ff<Int>(x);
		}
		void g1(int i);

		template<typename T>
		void f1(T x)
		{
			g1(x);	
		}

		template void f1(int);

		void g1(int i)
		{}

		void useF1()
		{
			f1(7);
		}
	}
}
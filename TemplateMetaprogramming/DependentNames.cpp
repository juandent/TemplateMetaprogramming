#include "stdafx.h"


namespace DependentNames
{
	template<typename T>
	struct B
	{};

	template<typename T>
	struct X : B<T> // "B<T>" is dependent on T
	{
		typename T::A* pa; // "T::A" is dependent on T
						   // (see below for the meaning of this use of "typename")
		void f(B<T>* pb) {
			static int i = B<T>::i; // "B<T>::i" is dependent on T
			pb->j++; // "pb->j" is dependent on T
		}
	};

	namespace BindingRules_ForNonDependentNames
	{
		void g(double) { std::cout << "g(double)\n"; }

		template<class T>
		struct S {
			void f() const {
				g(1); // "g" is a non-dependent name, bound now
			}
		};

		void g(int) { std::cout << "g(int)\n"; }

		void useG()
		{
			g(1); // calls g(int)

			S<int> s;
			s.f(); // calls g(double)
		}
	}

	namespace BindingRules_forDependentNames
	{
		// the lookup of a dependent name used in a template is postponed until the template arguments are known, at which time
		
		//  non - ADL lookup examines function declarations with external linkage that are visible from the template definition context
		//	ADL examines function declarations with external linkage that are visible from both the template definition context and the template instantiation context

		// (in other words, adding a new function declaration after template definition does not make it visible, except via ADL).

		std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
			for (int n : v) os << n << ' '; return os;
		}

		// an external libary
		namespace E {
			template<typename T>
			void writeObject(const T& t) {
				std::cout << "Value = " << t << '\n';
			}
		}

		namespace NonADL
		{
			// translation unit 1:
			// Programmer 1 wants to allow E::writeObject to work with vector<int>
			namespace P1 {
				std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
					for (int n : v) os << n << ' '; return os;
				}
				void doSomething() {
					std::vector<int> v;
					E::writeObject(v); // error: will not find P1::operator<<
				}
			}

			// translation unit 2:
			// Programmer 2 wants to allow E::writeObject to work with vector<int>
			namespace P2 {
				std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
					for (int n : v) os << n << ':'; return os << "[]";
				}
				void doSomethingElse() {
					std::vector<int> v;
					E::writeObject(v); // error: will not find P2::operator<<
				}
			}
			// In the above example, if non - ADL lookup for operator<< were allowed from the instantiation context, 
			// the instantiation of E::writeObject<vector<int>> would have two different definitions : 
			// one using P1::operator<< and one using P2::operator<<.Such ODR violation may not be detected by the linker, 
			// leading to one or the other being used in both instances.
		}
		namespace ADL
		{
			// To make ADL examine a user - defined namespace, either std::vector should be replaced by a user - defined class or 
			// its element type should be a user - defined class :
			namespace P1 {
				struct C { int i = 42;  };
				// if C is a class defined in the P1 namespace
				std::ostream& operator<<(std::ostream& os, const std::vector<C>& v) {
					for (C n : v) os << n.i; return os;
				}
				void doSomething() {
					std::vector<C> v;
					E::writeObject(v); // OK: instantiates writeObject(std::vector<P1::C>)
									   //     which finds P1::operator<< via ADL
				}
			}
		}
	}
}

namespace QualifiedNameLookup
{
	struct C { typedef int I; };
	typedef int I1, I2;
	extern int *p, *q;
	struct A { ~A() {} };
	typedef A AB;
	void useQualifiedNameLookup() {
		p->C::I::~I(); // the name I after ~ is looked up in the same scope as I before ::
					   // (that is, within the scope of C, so it finds C::I)
		q->I1::~I2();  // The name I2 is looked up in the same scope as I1
					   // that is, from the current scope, so it finds ::I2
		AB x;
		x.AB::~AB(); // The name AB after ~ is looked up in the same scope as AB before ::
					 // that is, from the current scope, so it finds ::AB
	}
}


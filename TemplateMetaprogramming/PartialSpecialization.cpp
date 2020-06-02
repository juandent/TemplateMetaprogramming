#include "stdafx.h"

using namespace std;

namespace PartialSpecialization
{

	template< typename T> class Widget
	{
	public:
		void Fun() { cout << " Widget<T>::Fun" << endl; }
		void Another() { cout << " Widget<T>::Another" << endl; }
	};


	// specialization of a func:
	template<>
	void Widget<char>::Fun()
	{
		cout << "Widget<char>::Fun" << endl;
	}

	template<> class Widget<int>
	{
		int state = 0;
	public:
		void Fun() { cout << " Widget<int>::Fun" << state  << endl; }
		void Another() { cout << " Widget<int>::Another" << state << endl; }
		int State() const { return state; }
	};


	// multiple template parameters
	template< typename T, typename U> class Gadget
	{
	public:
		void Fun() { cout << "Gadget<T,U>::Fun" << endl; }
		void Another() { cout << "Gadget<T,U>::Another" << endl; }
	};

	template<>
	void Gadget<char,int>::Fun()
	{
		cout << "Gadget<char,int>::Fun" << endl;
	}

	void useSpecialization()
	{
		Widget<char> w;
		w.Fun();
		w.Another();
		Widget<int> ww;
		ww.Fun();
		cout << ww.State() << endl;
		Gadget<char, int> g;
		g.Fun();
		g.Another();
	}

	// Creator policy interface (only for documentation purposes)
	template<typename T> class Creator
	{
	public:
		virtual T* Create() = 0;
		virtual ~Creator() {}
	};

	// different implementers of Creator policy
	template<typename T>
	struct OpNewCreator
	{
		template<typename ...Args>
		static T* Create(Args&&... args )
		{
			return new T{std::forward<Args>(args)...};
		}
	};

	template<typename T>
	struct MallocCreator
	{
		template<typename...Args>
		static T* Create(Args&&... args)
		{
			void* buf = std::malloc(sizeof(T));
			if (!buf) return nullptr;
			return new(buf) T{ std::forward<Args>(args)... };
		}
	};

	template<typename T>
	struct PrototypeCreator
	{
		PrototypeCreator(T* obj = nullptr) : pPrototype(obj) {}

		template<template<typename Created> class CreationPolicy>
		T* Create()
		{
			return pPrototype ? pPrototype->template Clone<CreationPolicy>() : nullptr;
		}

		T* getPrototype() { return pPrototype; }
		void setPrototype(T* obj) { pPrototype = obj; }
	private:
		T* pPrototype;
	};

	struct Empty
	{
		int a;
		int b;
		Empty(int a, int b) : a(a), b(b) {}
		Empty(const Empty& empty) : a{ empty.a }, b{ empty.b } {}
		template< template<typename Created> class CreationPolicy>
		Empty* Clone() { return CreationPolicy<Empty>().Create(*this); }
	};


	
	struct Dummy
	{
		int a;
		double b;
		Dummy(int a, double b) : a{ a }, b{ b } {}
	};

	//////////////////
	/// option 1:
	/// 
	template<typename CreationPolicy>
	struct DummyManager1 : public CreationPolicy
	{
		//...	
	};

	using MyDummyManager1 = DummyManager1<OpNewCreator<Dummy>>;

	////////////////
	/// option 2: (better)
	template< template<typename Created> class CreationPolicy >
	struct DummyManager2 : public CreationPolicy<Dummy>
	{
		// ....
	};

	using MyDummyManager2 = DummyManager2<OpNewCreator>;


	template<typename Created, template<class Created> class CreationPolicy>
	Created* Clone()
	{
		return CreationPolicy<Created>().Create();
	}
	
	void useCreatorPolicy()
	{
		auto p = OpNewCreator<Dummy>::Create(5, 4.75);
		cout << p->a << endl;
		auto q = OpNewCreator<Dummy>().Create(8, 99.99);

		auto r = OpNewCreator<Empty>().Create(12, 15);

		//auto rr = r->Clone<OpNewCreator<Empty>>();
		auto rr = r->Clone<OpNewCreator>();
		
		//auto t = PrototypeCreator<Empty>(r).template Create<OpNewCreator<Empty>>();
		auto t = PrototypeCreator<Empty>(r).template Create<OpNewCreator>();

		
		auto g = MallocCreator<Dummy>::Create(80, 29.55);
		cout << g->a << " " << g->b << endl;
	}
}


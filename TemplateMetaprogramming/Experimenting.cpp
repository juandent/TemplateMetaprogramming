#include "stdafx.h"

using namespace std;

template<typename T>
struct DefaultSmartPtrStorage
{
	using PointerType = T*;
	using ReferenceType = T&;

	DefaultSmartPtrStorage(PointerType p = nullptr) { setPointer(p); }
	bool isNull() const { return ptr == nullptr; }
protected:
	PointerType getPointer() const { return ptr; }
	void setPointer(PointerType p) { ptr = p; }
private:
	PointerType ptr;
};

template<typename T, typename U >
T* GetSubObj(U* obj)
{
	return static_cast<T*>(obj);
}

struct S
{
	int x;
};

struct Sample
{
	double d;
	Sample() {}
	~Sample() {}
	void Hello() { cout << "Hello" << endl; }
};

struct SubSample : public Sample
{
	
};

#if 0
template
<
	typename T,
	typename SS = Sample,
	template<typename> class Storage = DefaultSmartPtrStorage
>
struct SmartPtr : public SS, public Storage<T>, public S
{
	SmartPtr(T* p = nullptr) : pointee{ p }  , Storage<T>() {  }
	SmartPtr(const SmartPtr&) = delete;

	

	~SmartPtr() {}

	void dummy()
	{
		auto x = (Storage<T>*)(this)->getPointer();

		auto p = (Storage<T>*)(this);

		cout << typeid(p).name() << endl;

		cout << typeid(this).name() << endl;
		
		auto r = static_cast<Storage<T>*>(this);

		auto xp = this->getPointer();

		//auto xx = GetSubObj<Storage<T>>(this)->getPointer();
	}

private:
	T* pointee;
};
#endif

template<typename T>
struct EnforceNotNull;

/// <summary>
/// ChekingPolicies
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
struct NoChecking
{
	NoChecking() = default;
	template<typename T2>
	NoChecking(const EnforceNotNull<T2>& other)
	{}
	static void Check(T*) {}
};

template<typename T>
struct EnforceNotNull
{
	EnforceNotNull() = default;
	//template<typename T2>
	// EnforceNotNull(const NoChecking<T>& other)
	// {}
	static void Check(T* p)
	{
		if (!p)
			throw std::exception{ "Null Pointer Exception" };
	}
};


template
<
	typename T,
	template<typename> class CheckingPolicy
>
struct SmartPtr : public CheckingPolicy<T>
{
	SmartPtr(T* p = nullptr) : pointee{ p } {  }

	template<typename T2, template<typename> class CP2>
	SmartPtr(const SmartPtr<T2, CP2>& other)
		:  pointee(other.pointee), CheckingPolicy<T>( other)
	{
		//auto pCPT2 = static_cast<CheckingPolicy<T>*>(&other);
		constexpr auto eq = std::is_same<T2, SubSample>::value;
		static_assert(eq);
		constexpr auto eqq = std::is_same<T, Sample>::value;
		static_assert(eqq);
	}

	// SmartPtr( const SmartPtr<T,NoChecking>& other)
	// 	: EnforceNotNull(other)
	// {
	// 	
	// }

	template<typename T2, template<typename> class CP2>
	friend struct SmartPtr;


	~SmartPtr()
	{
		//Ownership<T>::Release(pointee);
	}
	T* operator->()
	{
		//typename ThreadingModel<T>::Lock guard(pointee);
		cout << "-> in SmartPtr" << endl;
		CheckingPolicy<T>::Check(pointee);
		return pointee;
	}

private:
	T* pointee;
};


void usePolicy()
{
	SmartPtr<SubSample, EnforceNotNull> spSample(new SubSample);

	SmartPtr<Sample, NoChecking> spSample2(spSample);
	//SmartPtr<Sample, EnforceNotNull> spSample3(spSample);
}



auto Device = [] {};
auto YearName = [] {};

template<typename interface>
struct Bind
{
	template<typename ClassName>
	Bind& to() { return *this; }

	Bind& operator()( string name ) { return *this; }
	void cc()
	{
		constexpr  bool same = std::is_same< decltype(Device), decltype(YearName)>::value;
	}
};

struct ISample
{
	
};


void useAccessSubobject()
{
	//SmartPtr<Sample> ptr{};
	//ptr.dummy();

	Bind<ISample>().to<Sample>().cc();

	
}

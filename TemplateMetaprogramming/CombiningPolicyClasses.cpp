#include "stdafx.h"
#include <mutex>

using namespace std;

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
	NoChecking(const NoChecking<T2>& other)
	{}

	template<typename T2>
	NoChecking(const EnforceNotNull<T2>& other)
	{}
	static void Check(T*) {}
};

template<typename T>
struct EnforceNotNull
{
	EnforceNotNull() = default;
	template<typename T2>
	EnforceNotNull(const EnforceNotNull<T2>& other)
	{
		
	}
	static void Check(T* p)
	{
		if (!p)
			throw std::exception{ "Null Pointer Exception" };
	}
};

////////////////
///ThreadingModel policy
template<typename T>
struct SingleThreaded
{
	template<typename T2>
	SingleThreaded(const SingleThreaded<T2>& other)
	{}

	struct Lock
	{
		Lock(T*) {}
		~Lock() {}
	};
};


template<typename T>
struct MultiThreaded
{
	MultiThreaded() = default;
	template<typename T2>
	MultiThreaded(const MultiThreaded<T2>& other) {}
	struct Lock
	{
		Lock(T* p) { multiMutex.lock(); }
		~Lock() { multiMutex.unlock(); }
	private:
		std::mutex multiMutex;
	};
};



/////////////
///Ownership Policy
template<typename T>
struct OwnPointer
{
	OwnPointer() = default;

	template<typename T2>
	OwnPointer(const OwnPointer<T2>& ) {}
	
	// OwnPointer( OwnPointer<T>&& other) {}
	static void Release(T* p) { delete p; }
};

template<typename T>
struct AliasPointer
{
	static void Release(T* p) {}
};

//////////////
///Customizing structure

template<typename T>
struct DefaultSmartPtrStorage
{
	using PointerType = T*;
	using ReferenceType = T&;

	template<typename T2>
	DefaultSmartPtrStorage(const DefaultSmartPtrStorage<T2>& other) : ptr{other.ptr} {}

	DefaultSmartPtrStorage(PointerType p = nullptr) { setPointer(p); }
	bool isNull() const { return ptr == nullptr; }


	template<typename T2>
	friend class DefaultSmartPtrStorage;
	
protected:
	PointerType getPointer() const { return ptr; }
	void setPointer(PointerType p) { ptr = p; }
private:
	PointerType ptr;
};



template
<
	typename T,
	template<typename> class CheckingPolicy,
	template<typename> class ThreadingModel,
	template<typename> class Ownership,
	template<typename> class Storage = DefaultSmartPtrStorage
>
struct SmartPtr : public CheckingPolicy<T>, public ThreadingModel<T>, public Ownership<T>, public Storage<T>
{
	SmartPtr(T* p = nullptr) : pointee{p} {  }


	template<typename T2, template<typename> class CP2, template<typename> class TM2, template<typename> class O2,
					template<typename> class S2>
	SmartPtr(const SmartPtr<T2, CP2, TM2, O2, S2>& other)
		: CheckingPolicy<T>(other), ThreadingModel<T>(other), Ownership<T>(other), Storage<T>(other), pointee(other.pointee)
	{
		constexpr size_t size = sizeof(pointee);
		int i = 0;
	}


	template<typename T2, template<typename> class CP2, template<typename> class TM2, template<typename> class O2,
		template<typename> class S2>
	friend class SmartPtr;

	
	~SmartPtr()
	{		
		Ownership<T>::Release(pointee);
	}
	T* operator->()
	{
		typename ThreadingModel<T>::Lock guard(pointee);
		cout << "-> in SmartPtr" << endl;
		CheckingPolicy<T>::Check(pointee);
		return pointee;
	}

private:
	T* pointee;
};

struct Sample
{
	Sample() {}
	~Sample() {}
	void Hello() { cout << "Hello" << endl; }
};

struct Other : Sample
{
	
};

namespace MixingPolicies
{
	void useSmartPtrBasic()
	{
		NoChecking<Sample> nc1;
		NoChecking<Other> nc2{ nc1 };
		
		SmartPtr<Other, EnforceNotNull, MultiThreaded, OwnPointer> spSample(new Other);

		constexpr size_t sample_size = sizeof(spSample);
		
		spSample->Hello();

		SmartPtr<Sample, NoChecking, MultiThreaded, OwnPointer> spSample2(spSample);
		constexpr size_t sample2_size = sizeof(spSample);
		
		Sample s{};
		Sample p{ s };
	}
	
}

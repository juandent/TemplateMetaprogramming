#include "stdafx.h"

#include "SampleTypes.h"

void Fun(Shape* pObj)
{
	typeid(*pObj).hash_code();
	
	if( typeid(*pObj) == typeid(Triangle))
	{
		
	}

	auto name = typeid(*pObj).name();
}



void use_typeid()
{
	auto p = new Triangle{};

	Fun(p);
	
}





class TypeInfo
{
public:
	TypeInfo() = default;
	TypeInfo(const std::type_info& ti)
	{
		pInfo = &ti;
	}
	TypeInfo(const TypeInfo& ti)
	{
		pInfo = ti.pInfo;
	}
	
	TypeInfo& operator=(const TypeInfo& ti)
	{
		pInfo = ti.pInfo;
		return *this;
	}
	
	// compatibility functions
	[[nodiscard]] bool before(const TypeInfo& ti) const
	{
		return pInfo->before(*ti.pInfo);
	}
	[[nodiscard]] const char* name() const
	{
		return pInfo->name();
	}

private:
	const std::type_info* pInfo = nullptr;
public:

	friend bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
	{ // or type_index
		return lhs.pInfo->hash_code() == rhs.pInfo->hash_code();
	}

	friend bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs.before(rhs);
	}

	friend bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs.before(rhs) || lhs == rhs;
	}

	friend bool operator>(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return rhs.before(lhs);
	}

	friend bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return rhs.before(lhs) || lhs == rhs;
	}
};

using namespace std;

void useTypeInfo()
{
	TypeInfo intT{ typeid(int) };
	cout << intT.name() << endl;

	vector<TypeInfo> vec;
	vec.emplace_back(typeid(Shape));
	vec.emplace_back(intT);

	cout << (intT == typeid(int)) << endl;
	
}



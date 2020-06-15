#include "stdafx.h"


class Interface
{
public:
	virtual void Fun() = 0;
	virtual ~Interface() {}
};


template<typename T, typename P>
Interface* MakeAdapter(const T& obj, const P& arg)
{
	class Local : public Interface
	{
		T& obj;
		P& arg;
	public:
		Local(const T& ob,  const  P& arg)
			: obj{ob}, arg{arg}
		{}
		virtual void Fun() override
		{
			obj._Call(arg);
		}
	};
	return new Local(obj, arg);
}

#pragma once

struct Something
{
private:
	int m_value;
public:
	Something(int val) : m_value{ val } {}
	int max(int a)
	{
		return std::max(m_value, a);
	}
	int max(int a, int b)
	{
		if (a > b)
		{
			if (m_value > a)
			{
				return m_value;
			}
			else
			{
				return a;
			}
		}
		else // a <=b
		{
			if (m_value > b)
			{
				return m_value;
			}
			else
			{
				return b;
			}
		}
	}
};


template<typename R, typename Class, typename ...Args>
struct Invoker
{
	Class m_object;

	//Invoker(R(Class::*p)(Args...));
	
	R Execute() { return R{}; }
};

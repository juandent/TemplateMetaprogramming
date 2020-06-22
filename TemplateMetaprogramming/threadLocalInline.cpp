#include "stdafx.h"
#include <thread>

struct MyData
{
	inline static std::string gName = "global";
	inline static thread_local std::string tName = "tls";
	std::string lName = "local";

	void print(const std::string& msg)
	{
		std::cout << msg << std::endl;
		std::cout << "- gName: " << gName << std::endl;
		std::cout << "- tName: " << tName << std::endl;
		std::cout << "- lName: " << lName << std::endl;

	}
}; 

inline thread_local MyData myThreadData;	// one object per thread

void foo();


void useThreadLocal()
{
	myThreadData.print("main() begins");

	myThreadData.gName = "thread1 name";
	myThreadData.tName = "thread1 name";
	myThreadData.lName = "thread1 name";
	myThreadData.print("main() later:");

	std::thread t(foo);
	std::thread u(foo);
	
	t.join();
	u.join();
	myThreadData.print("main() ends");
	
}

void foo()
{
	myThreadData.print("foo() begins");

	myThreadData.gName = "thread2 name";
	myThreadData.tName = "thread2 name";
	myThreadData.lName = "thread2 name";
	myThreadData.print("foo() end:");

}

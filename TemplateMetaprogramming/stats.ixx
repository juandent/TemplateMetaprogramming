module;


//#include <string>
//#include <fstream>

//import std.core;


export module stats;



import <fstream>;
import <iostream>;

//export 
import <string>;


//import std.core;

//export import std.core;

export constinit int configuration = 1;

#define CONFIGURATION configuration

export 
inline void MyFunc(std::string& s)
{
	std::ofstream os("file");

}

#if CONFIGURATION == configuration

export 
template<typename T>
void MyFunc(T&& t)
{
	if constexpr (std::is_reference<T>::value)
	{

	}
	if constexpr (std::is_reference<decltype(t)>::value)
	{

	}
	std::cout << "Hello\n";
}
#endif

void MyFunc(int a)
{
	std::string s = std::to_string(a);
}

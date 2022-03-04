


module stats;

import <fstream>;


void AnotherFuncModule(std::string s)
{
	std::ofstream os("file");
	
	MyFunc(std::move(s));
	MyFunc(5);
}
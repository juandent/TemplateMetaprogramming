#include "stdafx.h"

template<const char* str>
class Message
{
	
};


extern const char hello[] = "Hello world!";			// external linkage
const char hello11[] = "Hello world!";				// internal linkage


template<int* p> struct A
{};

int num;

A<&num> a;

constexpr int* pNum()
{
	return &num;
}

A<pNum()> b;

void useStringsInTemplates()
{
	Message<hello> msg;		// OK all C++ versions
	Message<hello11> msg11;	// OK since C++11

	static const char hello17[] = "Hello world!";	// no linkage
	Message<hello17> msg17;

	const char helloStack[] = "Hello world!";

	// Message<helloStack>  msgStack;	// ERROR
	// Message<"hello"> msgStack2;		// ERROR


	
}
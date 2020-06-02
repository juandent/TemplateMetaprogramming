#pragma once


int const length = 10;

class MiniBuffer
{
	char buf[length];
};

const int* const pLength = &length;

inline void f()
{
	const int* pLength = &length;
}
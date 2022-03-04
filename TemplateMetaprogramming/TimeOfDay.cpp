

#include "stdafx.h"

#include <chrono>
#include <iostream>

void useTimeOfDay()
{

	using namespace std;
	using namespace std::chrono_literals;

	auto td = std::chrono::hh_mm_ss{10.5h + 98min + 2020s + 0.5s};

	cout << td << endl;
	cout << td.hours() << endl;
	cout << td.minutes() << endl;
	cout << td.seconds() << endl;
	cout << td.subseconds() << endl;
	cout << td.to_duration() << endl;

}
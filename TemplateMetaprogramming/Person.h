#pragma once

#include <string>
#include <iostream>

struct Person
{
	std::string firstName;
	std::string lastName;

	friend std::ostream& operator<<(std::ostream& stream, Person const& p)
	{
		return stream << p.lastName << ", " << p.firstName << std::endl;
	}
};

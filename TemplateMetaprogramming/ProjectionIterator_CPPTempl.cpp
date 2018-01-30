#include "stdafx.h"

#include <vector>
#include <algorithm>

#include "Person.h"

#include "ProjectionIterator_CPPTempl.h"

void useProjectionIterator()
{
	using namespace IteratorByFacadeAccess;

	std::vector<Person> authors = { 
	{"Juan", "Dent"},
	{"Ignacio", "Trejos"},
	{"Raul", "Mendez"} };

	auto it = project(authors.begin(), &Person::firstName);
	auto f = *it;	// "Juan"
	assert(f == "Juan");

	++it;			// it => Ignacio Trejos
	auto s = *it;	// "Ignacio"
	assert(s == "Ignacio");

	--it;			// it => Juan Dent
	auto ss = *it;
	assert(ss == "Juan");

	auto t = it[1];	// it ==> Juan Dent, t => Ignacio Trejos
	auto tt = *it;
	assert(tt == "Juan");
	assert(t == "Ignacio");

	auto q = it[1];	//	q => Ignacio Trejos, it => Juan Dent
	assert(t == "Ignacio");
	assert(*it == "Juan");

	auto qq = it += 1;	// qq  == it => Ignacio Trejos
	assert(*it == "Ignacio");
	assert(*qq == "Ignacio");
	++qq;
	assert(*qq == "Raul");

	auto dist = qq - it;
	bool less = qq < it;
#if 1
	std::copy(project(authors.begin(), &Person::firstName),
		project(authors.end(), &Person::firstName),
			std::ostream_iterator<std::string>(std::cout, "\n"));
#endif
}


#include "stdafx.h"

namespace EBCO
{


	class Empty {
		using Int = int;  // type alias members don't make a class nonempty
	};

	class EmptyToo : public Empty {
	};

	class NonEmpty : public EmptyToo, public Empty {
	};

	class WithEmptyElements
	{
		EmptyToo t;
		Empty e;
//		long l;
//		int i;
	};

#pragma pack(show)
#pragma pack(push)
#pragma pack(1)

	class InheritingEmptyElements : public Empty, public EmptyToo
	{
		char c[3];
		long l;
		int i;
	};

#pragma pack(pop)
#pragma pack(show)

	class OnlyInheritingEmptyElements : public Empty, public EmptyToo
	{
	};


	void main()
	{
		std::cout << "sizeof(Empty):    " << sizeof(Empty) << '\n';
		std::cout << "sizeof(EmptyToo): " << sizeof(EmptyToo) << '\n';
		std::cout << "sizeof(NonEmpty): " << sizeof(NonEmpty) << '\n';

		std::cout << "sizeof(long): " << sizeof(long) << '\n';
		std::cout << "sizeof(WithEmptyElements): " << sizeof(WithEmptyElements) << '\n';

		std::cout << "sizeof(InheritingEmptyElements): " << sizeof(InheritingEmptyElements) << '\n';
		std::cout << "sizeof(OnlyInheritingEmptyElements ): " << sizeof(OnlyInheritingEmptyElements) << '\n';

		NonEmpty ne;
		Empty* peNe = static_cast<Empty*>(&ne);
		std::cout << std::hex << peNe << std::endl;
		EmptyToo* peToo = static_cast<EmptyToo*>(&ne);
		std::cout << std::hex << peToo << std::endl;
		Empty* peInToo = static_cast<Empty*>(peToo);
		std::cout << std::hex << peInToo << std::endl;


		EmptyToo et;
		EmptyToo* pet = &et;
		Empty* p = static_cast<Empty*>(&et);
		
		
		NonEmpty arr[2];
		Empty* pE0 = static_cast<Empty*>(&arr[0]);
		std::cout << std::hex << "<Empty*>(&arr[0]) " << pE0 << std::endl;

		EmptyToo* pE0Too = static_cast<EmptyToo*>(&arr[0]);
		std::cout << std::hex << "<EmptyToo*>(&arr[0])" << pE0Too << std::endl;

		Empty* pE0TooE = static_cast<Empty*>(pE0Too);
		std::cout << std::hex << "<Empty*>(pE0Too)" << pE0TooE << std::endl;


		Empty* pE1 = static_cast<Empty*>(&arr[1]);
		std::cout << std::hex << "<Empty*>(&arr[1])" << pE1 << std::endl;

	}

}